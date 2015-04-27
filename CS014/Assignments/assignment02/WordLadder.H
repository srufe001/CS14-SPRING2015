#ifndef WORDLADDER_H
#define WORDLADDER_H

#include <iostream>
#include <cstring>
#include <list>
#include <stack>
#include <queue>
#include <fstream>
#include <cstdlib>

using namespace std;

class WordLadder
{
 private:
    list <string> dictionary; //const list?
    
    bool wordDifferentChecker(const string & word, const string & compareWord)
    {
        int differentLetters = 0;
        for (int i = 0; i < 5; i++)
        {
            if(word.at(i) != compareWord.at(i))
            {
                differentLetters++;
            }
        }
        if (differentLetters == 1)
        {
            return true;
        }
        return false;
    }
    
    bool inDictionaryChecker(const string& word)
    {
        for(list<string>::iterator i = dictionary.begin(); i != dictionary.end(); i++)
        {
            if (word == *i)
            {
                return true;
            }
        }
        return false;
    }
    
 public:
    WordLadder(const string listFile) // Constructor that accepts the name of the dictionary file
    {
        ifstream fin;
        fin.open(listFile.c_str());
        if (!fin.is_open())
        {
            cout << "Error opening " << listFile << endl;
            exit(1);
        }
        else
        {
            string dic;
            while (fin >> dic)
            {
                dictionary.push_back(dic);
            }
            fin.close();
        }
    }
    
    void outputLadder(const string start, const string end) // accepts the start and end words and outputs to standard output the word ladder, if any
    {
        if ((!inDictionaryChecker(start)) || (!inDictionaryChecker(end))) // first, check to see if words are in dictionary
        {
            cout << "There is no word ladder from \"" << start << "\" to \"" << end << "\".\n";
            exit(1);
        }
        
        if (start == end)
        {
            cout << start << endl; // output start or end because they are the same
            return;
        }
        
        else
        {
            // Create a stack of strings.
            stack <string> wordLadder;
            // Push the start word on this stack.
            wordLadder.push(start);
            // Create a queue of stacks.
            queue <stack <string> > totalWordLadders;
            // Enqueue this stack.
            totalWordLadders.push(wordLadder);
            
            // While the queue is not empty
            while (!totalWordLadders.empty())
            {
                // For each word in the dictionary
                for(list<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
                {
                    // If a word is exactly one letter different (in any position) from the top string of the front stack
                    if (wordDifferentChecker(totalWordLadders.front().top(), *it))
                    {
                        if (*it == end)
                        {
                            // If this word is the end word, you are done! The front stack plus this word is your word ladder. Don’t forget to output this word ladder.
                            // Make a copy of the front stack.
                            stack <string> outLadder;
                            // copying the ladder over in reverse order
                            outLadder.push(*it); // copy last element in
                            while (!totalWordLadders.front().empty())
                            {
                                // Push the found word onto the copy.
                                // Enqueue the copy.
                                outLadder.push(totalWordLadders.front().top());
                                totalWordLadders.front().pop();
                            }
                            
                            // output the ladder
                            cout << outLadder.top();
                            outLadder.pop();
                            while (!outLadder.empty())
                            {
                                cout << ' ' << outLadder.top();
                                outLadder.pop();
                            }
                            
                            cout << endl; // output newline
                            
                            return;
                        }
                        stack<string> tempLadder = totalWordLadders.front();
                        tempLadder.push(*it); // add this ladder to queue
                        totalWordLadders.push(tempLadder);
                        
                        dictionary.erase(it);
                        it--;
                    }
                // End of for-loop.
                }
                // Dequeue front stack (i.e., remove it from the queue)
                totalWordLadders.pop();
            }
        }
    }
};

#endif