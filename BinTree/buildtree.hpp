#include <vector>
#include <algorithm>

#include "BinNode.hpp"

template <typename T>
BinNodePosi(T) BuildTree1(std::vector<T> & pre, std::vector<T> & In) {
    return BuildBinaryTree1(pre.begin(), pre.end(), In.begin(), In.end());
}

template <typename T, typename inputiterator>
BinNodePosi(T) BuildBinaryTree1(inputiterator pre_first, inputiterator pre_last,
        inputiterator in_first, inputiterator in_last) {
    
    if(pre_first == pre_last) return NULL;
    if(in_first == in_last) return NULL;

    BinNodePosi(T) root = new BinNode<T>(*pre_first);
    inputiterator inRootPos = find(in_first, in_last, *pre_first);
    int leftSize = distance(in_first, inRootPos);

    root->lchild = BuildBinaryTree1(next(pre_first), next(next(pre_first), leftSize),
            in_first, next(inRootPos));
    root->rchild = BuildBinaryTree1(next(next(pre_first), leftSize), pre_last,
            next(inRootPos), in_last);

    return root;
}

template <typename T>
BinNodePosi(T) BuildTree2(std::vector<T> & post, std::vector<T> & In) {
    return BuildBinaryTree2(post.begin(), post.end(), In.begin(), In.end());
}

template <typename T, typename inputiterator>
BinNodePosi(T) BuildBinaryTree2(inputiterator post_first, inputiterator post_last,
        inputiterator in_first, inputiterator in_last) {

    if(post_first == post_last) return NULL;
    if(in_first == in_last) return NULL;

    BinNodePosi(T) root = new BinNode<T>(*prev(post_last));
    inputiterator inRootPos = find(in_first, in_last, *prev(post_last));
    int leftSize = distance(in_first, inRootPos);
    inputiterator post_left_last = next(post_first, leftSize);

    root->lchild = BuildBinaryTree2(post_first, post_left_last,
            in_first, inRootPos);
    root->rchild = BuildBinaryTree2(post_left_last, prev(post_last),
            next(inRootPos), in_last);

    return root;
}
