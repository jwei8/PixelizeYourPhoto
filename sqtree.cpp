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
  // Your code here.
  
  stats s(imIn); 
  im_width = imIn.width();
  im_height = imIn.height();

  pair<int, int> upper_left = make_pair(0, 0);

  buildTree(s, upper_left, im_width, im_height, tol);

  



  

}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {
  // Your code here.
   

  // if (getVar(ul,w,h) > tol) {
  // Node *returnNode = new Node (pair<int, int>(0,0), 1,1);
  //   return returnNode;
  // } else {

  //   Node *child_NW = new Node (ul, w,h);
  //   Node *child_NE = new Node (make_pair(ul.first + w-1, ul.second), w,h);
    
  // }

  return NULL;



}

  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  // Your code here.
  PNG result(10,10);

  // return render_recursive(root);
  return result;

}

void SQtree::render_recursive(SQtree:: Node *node, PNG &im) {
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
