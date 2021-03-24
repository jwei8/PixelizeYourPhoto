/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG & imIn, double tol) {
  stats s(imIn); 
  pair<int, int> upper_left = make_pair(0, 0);

  root = buildTree(s, upper_left, imIn.width(), imIn.height(), tol);
  
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {
  Node * current = new Node(ul, w, h, s.getAvg(ul, w, h), s.getVar(ul, w, h));
  
  if ((w == 1 && h == 1) || s.getVar(ul, w, h) < tol) {
    return new Node(ul, w, h, s.getAvg(ul, w, h), s.getVar(ul, w, h));
  }

  double totalMinVariability = s.getVar(ul,w,h);
  pair<int,int> minVarUL = ul;
  
  for (int y = ul.second; y < ul.second + h; y++) {
    for (int x = ul.first; x < ul.first + w; x++) {
      if (x == ul.first && y == ul.second) {
        continue;
      }

      if ( x== ul.first && y !=ul.second ) {
      double upVar = s.getVar(ul, w, y - ul.second);
      double downVar = s.getVar(make_pair(x, y), w, h-y + ul.second);
      double currentMaxVariability = max(upVar, downVar);
      if (currentMaxVariability < totalMinVariability) {
        totalMinVariability = currentMaxVariability;
        minVarUL.first = x;
        minVarUL.second = y;
      }
      }

      if ( x != ul.first && y == ul.second) {
      double leftVar = s.getVar(ul, x - ul.first, h);
      double rightVar = s.getVar(make_pair(x, y), w-x+ul.first, h);
      double currentMaxVariability = max (leftVar, rightVar);

      if (currentMaxVariability < totalMinVariability) {
        totalMinVariability = currentMaxVariability;
        minVarUL.first = x;
        minVarUL.second = y;
      }
      }

      double NWVar = s.getVar(ul, x-ul.first, y-ul.second);
      double NEVar = s.getVar(make_pair(x, ul.second), w-x+ul.first, y);
      double SWVar = s.getVar(make_pair(ul.first, y), x-ul.first, h-y+ul.second);
      double SEVar = s.getVar(make_pair(x, y), w-x+ul.first, h-y+ul.second);
      double currentMaxVariability = max(NWVar, max (NEVar, max(SWVar, SEVar)));
      if (currentMaxVariability < totalMinVariability) {
        totalMinVariability = currentMaxVariability;
        minVarUL.first = x;
        minVarUL.second = y;
      }
    }
  }

  if (minVarUL.second == ul.second && minVarUL.first == ul.first) {
    return current;
  } else if (minVarUL.second == ul.second) {
    // first !=0, second ==0, vertical line
    current->SW = buildTree(s, ul, minVarUL.first - ul.first , h, tol);
    current->SE = buildTree(s, minVarUL, w - minVarUL.first + ul.first, h, tol);
  } else if (minVarUL.first == ul.first) {
    // second not 0, first is 0, horizontal line
    current->NW = buildTree(s, ul, w, minVarUL.second - ul.second, tol);
    current->SW = buildTree(s, minVarUL, w, h - minVarUL.second + ul.second, tol);
  } else {

    //two lines devide
    pair<int,int> NEpair = make_pair(minVarUL.first, ul.second);
    pair<int,int> SWpair = make_pair(ul.first, minVarUL.second);
    current->NW = buildTree(s, ul, minVarUL.first - ul.first, minVarUL.second - ul.second, tol);
    current->NE = buildTree(s, NEpair, w - minVarUL.first + ul.first, minVarUL.second -ul.second, tol);
    current->SW = buildTree(s, SWpair, minVarUL.first - ul.first, h - minVarUL.second + ul.second, tol);
    current->SE = buildTree(s, minVarUL, w - minVarUL.first +ul.first, h - minVarUL.second + ul.second, tol);
  }


  return current;



}
  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  // Your code here.
  PNG result (root->width, root->height);
  render_recursive(root, result);
  return result;

}

void SQtree::render_recursive(Node *node, PNG &im) {
  if (node->NW == NULL) {

    for (int x=0; x < node->width; x++) {
      for (int y=0; y<node->height; y++) {
        RGBAPixel *pixel = im.getPixel(node->upLeft.first + x, node->upLeft.second + y);
        *pixel = node->avg;
      }
    }
  } else {
    render_recursive(node->NW, im);
    render_recursive(node->NE, im);
    render_recursive(node->SW, im);
    render_recursive(node->SE, im);

  }
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  clearAll(root);
  root = NULL;
 
}

void SQtree::clearAll(Node * & node) {
  if (node == NULL) {
    return;
  }
  else {

    clearAll(node->NW);
    clearAll(node->NE);
    clearAll(node->SW);
    clearAll(node->SE);

    node->NW = NULL;
    node->NE = NULL;
    node->SW = NULL;
    node->SE = NULL;
    

    delete node;

    node = NULL;
  }
}



void SQtree::copy(const SQtree & other) {
  // Your code here.  Node *curr = other.head_;
  //root = copyAll(other, other.root);
}

void SQtree::copyAll(const SQtree & other, Node * & currNode) {
  if (currNode == NULL) {
    return;
  } else {
    return;
  }
}


int SQtree::size() {
  // Your code here.
  //return calc_size(root);

  return 0;
  

}


int SQtree::calc_size(SQtree::Node* root){
  int size = 1;
  // if(root->NE == NULL && root->NW == NULL && root->SW==NULL && root->SE == NULL) {
  //   return size;
  // }

  // if (root->NE != NULL) {
  //   size = size + calc_size(root->NE);
  // }

  //   if (root->NW != NULL) {
  //   size = size + calc_size(root->NW);
  // }

  //   if (root->SE != NULL) {
  //   size = size + calc_size(root->SE);
  // }

  //   if (root->SW != NULL) {
  //   size = size + calc_size(root->SW);
  // }

  return size;

}

