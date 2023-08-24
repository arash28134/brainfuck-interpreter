/*Brainfuck-Interpreter
Copyright (C) 2023 Ali Atashrooz

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    while (true)
    {
        vector<int> tape(30000, 0); // brainfuck tape with 30000 cells
        int ptr = 0;                // pointer to the current cell (memory address)
        int code_ptr = 0;           // pointer to current code instruction

        cout << "> ";
        
        string code;
        getline(cin, code);

        while (code_ptr < code.size())
        {
            char instruction = code[code_ptr];

            // brainfuck instructions
            // https://en.wikipedia.org/wiki/Brainfuck#Language_design
            switch (instruction)
            {
            case '>':   // increment cell pointer
                ++ptr;
                break;

            case '<':   // decrement cell pointer
                --ptr;
                break;

            case '+':   // increment byte at ptr cell
                ++tape[ptr];
                break;

            case '-':   // decrement byte at ptr cell
                --tape[ptr];
                break;

            case '.':   // print byte at ptr cell
                cout << (char)tape[ptr];
                break;

            case ',':   // accept one byte of input, store it's value at ptr cell
                tape[ptr] = cin.get();
                break;

            case '[':   // start a loop
                if (tape[ptr] == 0)
                {
                    int loop_count = 1;
                    while (loop_count > 0)
                    {
                        ++code_ptr;
                        if (code[code_ptr] == '[')
                            ++loop_count;
                        else if (code[code_ptr] == ']')
                            --loop_count;
                    }
                }
                break;

            case ']':   // end a loop
                if (tape[ptr] != 0)
                {
                    int loop_count = 1;
                    while (loop_count > 0)
                    {
                        --code_ptr;
                        if (code[code_ptr] == '[')
                            --loop_count;
                        else if (code[code_ptr] == ']')
                            ++loop_count;
                    }
                }
                break;
            
            // for closing the program
            case 'c':
                return 0;
                break;
            
            default:
                cout << "\nUnrecognized character: " << code[code_ptr];
                break;
            }

            ++code_ptr;
        }

        cout << endl;
    }

    return 0;
}