#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"
// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp



/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * @param start The start of the AVL Tree
 * @param val1 A value of the file size query range.
 * @param val2 A value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range. In ascending or descending order 
 *         depending on the given parameters.
 * @note This function recursively traverse the tree in preorder if the given parameter are val1 < val2 the
 *       return vector would be in ascending order or if val1 >= val2 then the return vector would be in descending order
 */
inline std::vector<File*> getAscendORDescend(Node* start, int val1, int val2){
    //Result Value is set to a empty Vector 
    std::vector<File*> result;
    //Base case
    if(start == nullptr){
        return result;
    }

    //Ascending Recurison
    if(val1 < val2){
        std::vector<File*> leftResult = getAscendORDescend(start->left_, val1,val2);
        result.insert(result.begin(), leftResult.begin(), leftResult.end());


        if (val1 <= start->size_ && start->size_ <=val2) {
            result.insert(result.end(),start->files_.begin(),start->files_.end());
        }
 
        std::vector<File*> rightResult = getAscendORDescend(start->right_, val1,val2);
        result.insert(result.end(), rightResult.begin(), rightResult.end());
    }
    //Descending Recursion
    if(val1 >= val2){

        std::vector<File*> rightResult = getAscendORDescend(start->right_, val1,val2);
        result.insert(result.begin(), rightResult.begin(), rightResult.end());

        if (val1 <= start->size_ && start->size_ <=val2) {
            result.insert(result.end(),start->files_.begin(),start->files_.end());
        }

        std::vector<File*> leftResult = getAscendORDescend(start->left_, val1,val2);
        result.insert(result.end(), leftResult.begin(), leftResult.end());
    }
    return result;
}

/**
 * @brief remove all 
 * @param A vector of std::vector<FileTrieNode*>
 * @note Recursively call delete while the vector is full 
 */
inline void FileTrieDestructor(std::vector<FileTrieNode*> &head){
     /**
      * Base case
      * Don't do anything since there is nothing
     */
    if(head.empty()){
        return;
    }
    /**
     * Not empty loop through vector and delete it 
     */
    else{
        for(auto x : head){
            FileTrieDestructor(x->next);
            delete x;
        }
    }
}

/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */

std::vector<File*> FileAVL::query(size_t min, size_t max) {
    return getAscendORDescend(this->root_,min,max);
}

                          
void FileTrie::addFile(File* f){
    std::string name = f->getName();
    if(name.empty()){
        return;
    }
    for(char c : name){
        //File name is illegal 
        if(!(isalpha(c)|| c== '.' || isdigit(c))){
            return;
        }
    }
        auto temp = head;
        //Insert at Root ""
        temp->matching.insert(f);
        //Looping through the entire string 
        for(char c : name){
            c = tolower(c);
            //Going to the FileTrieNode_Next with Matching Char
            bool notfound = true;
            for(auto vec : temp->next){
                if(vec->stored == c){
                    temp = vec;
                    temp->matching.insert(f);
                    notfound = false;
                }
            }
            //Createa a new FileTrieNoe with Matching Char if it doesn't exist 
            if(notfound){
                temp->next.push_back(new FileTrieNode(c,f));
                temp = (temp->next.back());
            }
        }
        temp = nullptr;
}

std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const{
    auto temp = head;
    
    for(auto c : prefix){
        bool notfound = true;
        for(auto vec : temp->next){
            if(vec->stored == c){
                temp = vec;
                notfound = false;
                break;
            }
        }
        if(notfound){
            return std::unordered_set<File*>();
        }
    }
    return temp->matching;
}


FileTrie::~FileTrie(){
    //clear the map assuming we still want to keep all the files or else just a for each loop and calling the destructor for the File
    for(auto x: head->next){
        delete x;
    }
}
