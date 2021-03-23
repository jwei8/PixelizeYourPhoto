/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"
#include <float.h>

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
  // Your code here.
  
  stats s(imIn); 
  //width = imIn.width();
  //height = imIn.height();

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
    return current;
  }

  double totalMinVariability = DBL_MAX;
  pair<int,int> minVarUL = ul;
  
  for (int y = ul.second; y < ul.second + h; y++) {
    for (int x = ul.first; x < ul.first + w; x++) {
      double NWVar = s.getVar(ul, x, y);
      double NEVar = s.getVar(make_pair(x, 0), w-x, y);
      double SWVar = s.getVar(make_pair(0, y), x, h-y);
      double SEVar = s.getVar(make_pair(x, y), w-x, h-y);
      double currentMaxVariability = max(NWVar, max (NEVar, max(SWVar, SEVar)));
      if (currentMaxVariability < totalMinVariability) {
        totalMinVariability = currentMaxVariability;
        minVarUL.first = x;
        minVarUL.second = y;
      }
    }
  }

  if (minVarUL.second == 0 && minVarUL.first == 0) {
    return current;
  } else if (minVarUL.second == 0) {
    current->SW = buildTree(s, ul, minVarUL.first, h, tol);
    current->SE = buildTree(s, minVarUL, w - minVarUL.first, h, tol);
  } else if (minVarUL.first == 0) {
    current->NE = buildTree(s, ul, w, minVarUL.second, tol);
    current->SE = buildTree(s, minVarUL, w, h - minVarUL.second, tol);
  } else {
    pair<int,int> NEpair = make_pair(minVarUL.first, ul.second);
    pair<int,int> SWpair = make_pair(ul.first, minVarUL.second);
    current->NW = buildTree(s, ul, minVarUL.first, minVarUL.second, tol);
    current->NE = buildTree(s, NEpair, w - minVarUL.first, minVarUL.second, tol);
    current->SW = buildTree(s, SWpair, minVarUL.first, h - minVarUL.second, tol);
    current->SE = buildTree(s, minVarUL, w - minVarUL.first, h - minVarUL.second, tol);
  }


  return current;



}

  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  // Your code here.
  PNG result;

  // return render_recursive(root);
  return result;

}

void SQtree::render_recursive(Node *node) {
  // PNG result (width, height);
  // if (node->NE == NULL || node->NW == NULL || node->SW == NULL || node->SE == NULL) {
  //   for (int x=0; x < width; x++) {
  //     for (int y=0; y < height; y++) {
  //       RGBAPixel * pixel = result.getPixel(x,y);
  //       *pixel = node->avg;
  //     }
  //   }

  //   return result;
  // }
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  // Your code here.

  // clearAll(root);
  // root = NULL;
 
}

void SQtree:: clearAll(Node * & node) {
  // if (node == NULL) {
  //   return;
  // }
  // else {

  //   clearAll(node->NW);
  //   clearAll(node->NE);
  //   clearAll(node->SW);
  //   clearAll(node->SE);

  //   node -> NW = NULL;
  //   node -> NE = NULL;
  //   node -> SW = NULL;
  //   node -> SE = NULL;
    

  //   delete node;

  //   node = NULL;
  // }
}



void SQtree::copy(const SQtree & other) {
  // Your code here.  Node *curr = other.head_;
  //root = copy_helper(other);
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

