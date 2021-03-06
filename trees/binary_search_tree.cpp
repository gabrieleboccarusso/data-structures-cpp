#include <iostream>

using std::cout;
using std::endl;
using std::string;

class tree
{
  private:
    struct node {
      int data;
      node * left;
      node * right;
    };
    int height;
    node * root;
 public:
    // constructor
    tree (int value)
    {
      root = new node;
      root -> data = value;
      root -> right = NULL;
      root -> left = NULL;
    }

    // note: iterative insertion into a binary tree,
    // may be more efficient/readable using recursion
    void insert (int number)
    {
      // beginning from the root node
      node * ptr = root;
      bool insert = false;

      // while it is not inserted
      while(!insert)
      {
        // if is greater than root
        if (number > ptr -> data)
        { // if there is no node
          if (ptr -> right == NULL)
          { // create node, assign value and exit loop
            ptr -> right = new node;
            ptr -> right -> data = number;
            insert = true; 
          }
          else
          { //  otherwise we go deep one level
            ptr = ptr -> right;
          }
        }
        // same things for the left
        else if(number < ptr -> data)
        {
          if (ptr -> left == NULL)
          {
            ptr -> left = new node;
            ptr -> left -> data = number;
            insert = true;
          }
          else
          {
            ptr = ptr -> left;
          }
        }
        else 
        {
          cout << "the number is already in the tree\n or unknown error";
          insert = true;
        }
      }

      return;
    }

    node * get_root()
    {
      return root;
    }

    // the lookup method returns a pointer 
    //to the node and takes three arguments
    // * the number to search in the tree
    // the node to begin with
    // * if the want the node itself ("child") or its parent ("father")
    node* lookup(int number, string node_type = "child", node * ptr = NULL)
    {
      // the node to return
      node* ret_ptr;

      // if no node is given the research will began from the
      // root node of the class
      if (ptr == NULL) ptr = root;

      // if the node to search is the root
      // we return the the root as ret_ptr
      if (ptr -> data == number)
      {
        ret_ptr = ptr;
        ptr = NULL; // so we don't enter the loop
      }

      while(ptr) // while ptr isn't NULL
      {
        if(number > ptr -> data) // go right
        { 
          if (number == ptr -> right -> data)
          { // if we want the father we return the current pointer
            if (node_type == "father" ) 
            {
              ret_ptr = ptr;
              ptr = NULL; // exit the loop
            } 
            // otherwise we set the pointer to the wanted node
            else if (node_type == "child") 
            { 
              ret_ptr = ptr -> right;
              ptr = NULL; // exit the loop
            }
          }

          else ptr = ptr -> right;
        }
        // same as the if, but with the left node
        else if(number < ptr -> data)
        {
          if (number == ptr -> left -> data)
          {
            if (node_type == "father" ) 
            {
              ret_ptr = ptr;
              ptr = NULL; // exit the loop
            } 
            else if (node_type == "child") 
            {
              ret_ptr = ptr -> left;
              ptr = NULL; // exit the loop
            }
          }
          else ptr = ptr -> left;
        }
      }

     return ret_ptr;
    }

    void remove(int number)
    { // incomplete attempt at the method that delete a node, for now on a fixed case
      node * parent = lookup(number, "father");
      node * current;
      
      // getting the child this way is faster than
      // calling again the lookup function
      if (parent -> right && parent -> right -> data == number)
      {
        current = parent -> right;
      }
      else if (parent -> left && parent -> left -> data == number)
      {
        current = parent -> left;
      }

      // if the node to delete is a leaf
      if (!current -> right && !current -> left)
      {
        if (parent -> right == current)
         parent -> right = NULL;
        else parent -> left = NULL;

        delete current;
      }

      return;
    }
};

int main()
{
  tree my_tree(50);
  my_tree.insert(40);
  my_tree.insert(30);
  my_tree.insert(25);
  my_tree.insert(15);

  my_tree.remove(15);
  if (my_tree.lookup(15) == NULL)
    cout << "b";
 

  return 0;
}