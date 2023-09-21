#include "HuffmanTree.hpp"

HuffmanNode *tree = NULL;// makes a global tree
HuffmanTree::HuffmanTree(){}// constructor 

HuffmanNode* decomTree(std :: string input){// turns the postorder string to inorder with postfix to infix conversion
   HuffmanNode* l;// creates left node 
   HuffmanNode* r;// creates right node 

   std :: stack<HuffmanNode*> stack;
   for(int i = 0; input[i] != '\0'; i++){
      
      if(input[i]=='L'){// if L gets the next character in the string and creates a leaf node for it 
         i++;
         HuffmanNode * leaf = new HuffmanNode(input[i],0);
         stack.push(leaf);//
      }

      else{// only other option is B
         r = stack.top();
         stack.pop();
         l = stack.top();
         stack.pop();
         
         HuffmanNode *root = new HuffmanNode('\0', 0, nullptr, l, r);// creates a branch node and puts back into stack
         stack.push(root);
      }
   }
   return stack.top();// returns root node 
}


std :: string original(std:: string input, HuffmanNode* root){// returns the original string 
   std::string str;
   
   HuffmanNode* branch = root;// sets branch (just a name not a actual branch) to root
   for(int i = 0; input[i] != '\0'; i++){
      if (input[i] == '1'){// if string[i] = 1 the pointer goes right
         branch = branch->right;
      }
      else if (input[i] == '0'){// if string[i] = 0 pointer goes left
         branch = branch->left;
         
      }
       if (branch->isLeaf()){// if its a leaf we add the character to the string 
         str += branch->getCharacter();
         branch = root;
         }    
   }
     return str;// original string 
}

void encode(HuffmanNode *root, std:: string str, std::map<char, std :: string> &bMap){
   if (root == nullptr)// checks if root is empty
      return;
   if(root->isLeaf())
      bMap[root->getCharacter()] = (str != "") ? str : "1";// if node is leaf gets the character 
   
   encode(root->left, str + "0", bMap);// calls encode and adds '0' to the string when moved to left node 
   encode(root->right, str + "1", bMap);// calls encode and adds '1' to the string when moved to right node
}//end encode 

HuffmanNode* build_tree(std :: vector< std :: pair<char, int> > &alph){
   HeapQueue<HuffmanNode*,HuffmanNode::Compare> HQ;
   for (std :: vector< std :: pair<char, int> >:: iterator itor = alph.begin(); itor != alph.end(); itor++)// iterates through the map of characters and frequencies 
   {
      HuffmanNode* leaf = new HuffmanNode(itor->first, itor->second);// creates new node with character and its frequency 
      HQ.insert(leaf);// insert new node into the heap queue 
   }
   HuffmanNode* root = NULL;
   while(HQ.size() > 1)
   {
      HuffmanNode* l;// creates left node 
      HuffmanNode* r;// creates right node 
      l = HQ.min();// gives left node info form heap queue
      HQ.removeMin();
      r = HQ.min();
      HQ.removeMin();
      root = new HuffmanNode ('\0', l->getFrequency()+ r->getFrequency(), nullptr, l, r);// makes a parent node with the combined frequencies of the left and right node 
      HQ.insert(root);
   } 
   return root;
}// end build_tree

std :: vector< std :: pair<char, int> > freqMap(std :: string input) {
   std :: map<char, int> freqmap;
   std :: vector< std :: pair <char, int> >freqVector;
   for (unsigned int i = 0; i < input.size(); i++) {
        if (freqmap.find(input[i]) == freqmap.end()) {// sees if character is in map 
            freqmap.insert(std :: make_pair(input[i], 1));
        }
        else
            freqmap[input[i]] += 1;// if character is already part of map increases frequency by 1
    }
   for (std :: map<char, int>::iterator itor = freqmap.begin();
      itor != freqmap.end(); itor++) {
      freqVector.push_back(std :: make_pair(itor->first, itor->second));// converts map to vector 
   }
   return freqVector;
}//end freqMap

std :: string serialize(HuffmanNode *root){
   std :: string left;
   std :: string right;
   std :: string str;
   if (root->isBranch()){
      left = serialize(root -> left);// calls serialize and adds to the left string whats is returned
      right = serialize(root -> right);// calls serialize and adds to the right string whats is returned
      str += left;
      str += right;
      str += "B";//adds B to string when the node is a branch
      return str;
   }
   else
   {
      str += "L";
      str+= root->getCharacter();// if node is leaf gets character and adds L in front of it 
      return str;\
   }
}// end serialize 

std::string HuffmanTree::compress(std::string inputStr){
   std :: string out; 
   std :: map <char, std :: string> codeTree; 
   std :: vector< std :: pair<char, int> > freqVec = freqMap(inputStr);// calls freqmap and converts to a vector 
   tree = build_tree(freqVec);// builds tree out of the freVector 
   encode(tree,"",codeTree);// creates a map with the binary code of the character 
   for (unsigned int i = 0; i < inputStr.size(); i++){
      out = out + codeTree[inputStr[i]];// code tree holds a character and a binary string from the tree
   }
   return out; 
}// end compress

std::string HuffmanTree :: serializeTree() {
   std::string serializeString = serialize(tree);// serializes the tree into a string
   return serializeString;
}// end serializeTree

std::string HuffmanTree :: decompress(const std::string inputCode, const std::string serializedTree){
   HuffmanNode* root = decomTree(serializedTree);// returns the tree
   std :: string out = original(inputCode, root);//returns the original string
   return out;
}// end decompress

