#include<bits/stdc++.h>
using namespace std;

class symbol_info   //class modification needed
{
private:
    string name;
    string type;

    string symbol_type; //variable/array/function
    string data_type;  //int/float/void/
    string return_type;  //functions
    string param_details;  //functions
    int array_size;  //arrays
    int param_count;

    //getters and setters? below

    // Write necessary attributes to store what type of symbol it is (variable/array/function)
    // Write necessary attributes to store the type/return type of the symbol (int/float/void/...)
    // Write necessary attributes to store the parameters of a function
    // Write necessary attributes to store the array size if the symbol is an array

public:
    symbol_info(string name, string type)
    {
        this->name = name;
        this->type = type;

        this->symbol_type;
        this->data_type;
        this->return_type;
        this->param_details;
        this->array_size = 0;
        this->param_count = 0;
    }
    string getname()
    {
        return name;
    }
    string get_type()
    {
        return type;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    void set_type(string type)
    {
        this->type = type;
    }
    // Write necessary functions to set and get the attributes

    string get_symbol_type()
    {
        return symbol_type;
    }
    string get_data_type()
    {
        return data_type;
    }
    string get_return_type()
    {
        return return_type;
    }
    string get_param_details()
    {
        return param_details;
    }
    int get_array_size()
    {
        return array_size;
    }
    int get_param_count()
    {
        return param_count;
    }
    void set_symbol_type(string symbol_type)
    {
        this->symbol_type = symbol_type;
    }
    void set_data_type(string data_type)
    {
        this->data_type = data_type;
    }
    void set_return_type(string return_type)
    {
        this->return_type = return_type;
    }
    void set_param_details(string param_details)
    {
        this->param_details = param_details;
    }
    void set_array_size(int array_size)
    {
        this->array_size = array_size;
    }
    void set_param_count(int param_count)
    {
        this->param_count = param_count;
    }
    ~symbol_info()
    {
        // Write necessary code to deallocate memory, if necessary
    }
};