#include "symbol_info.h"

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    vector<list<symbol_info *>> table;

    int hash_function(string name)
    {
        // write your hash function here
        // Convert to ASCII then mod with table size = index generated
        //ab -> idx
        // ba -> idx
        int sum = 0;
        for (int i = 0; i < name.length(); i++) 
        {
            sum += (int)name[i];
        }
        return sum % bucket_count;
    }

public:
    scope_table();
    scope_table(int bucket_count, int unique_id, scope_table *parent_scope);
    scope_table *get_parent_scope();
    int get_unique_id();
    symbol_info *lookup_in_scope(symbol_info* symbol); //this needs to be done
    bool insert_in_scope(symbol_info* symbol);  //this needs to be done
    bool delete_from_scope(symbol_info* symbol);  //this needs to be done
    void print_scope_table(ostream& outlog);  //this needs to be done
    ~scope_table();

    // you can add more methods if you need
};

// complete the methods of scope_table class

scope_table::scope_table()
{
    this->bucket_count = 10;
    this->unique_id = 0;
    this->parent_scope = NULL;
    table.resize(bucket_count);
}

//main constructor
scope_table::scope_table(int bucket_count, int unique_id, scope_table *parent_scope)
{
    this->bucket_count = bucket_count;
    this->unique_id = unique_id;
    this->parent_scope = parent_scope;
    table.resize(bucket_count);
}

//parent scope
scope_table* scope_table::get_parent_scope()
{
    return parent_scope;
}

//scope ID
int scope_table::get_unique_id()
{
    return unique_id;
}

//lookup in the current scope
symbol_info* scope_table::lookup_in_scope(symbol_info* symbol)
{
    int index = hash_function(symbol->getname());
    list<symbol_info *>::iterator it;

   for (it = table[index].begin(); it != table[index].end(); it++)
   {
       if ((*it)->getname()==symbol->getname())
       {
        return *it;  //when found
       }
   }
   return NULL; // when not found
}

bool scope_table::insert_in_scope(symbol_info* symbol)
{
    if (lookup_in_scope(symbol) != NULL)
    {
        return false; //exists already
    }

    int index = hash_function(symbol->getname());
    table[index].push_back(symbol);

    return true; //inserted a new symbol
}

bool scope_table::delete_from_scope(symbol_info* symbol)
{
    int index = hash_function(symbol->getname());
    list<symbol_info*>::iterator it;

    for (it = table[index].begin(); it != table[index].end(); it++)
    {
        if ((*it)->getname()==symbol->getname())
        {
            table[index].erase(it);
            return true;  // return true after deleting the symbol
        }
    }
    return false;  //didn't find the symbol
}

void scope_table::print_scope_table(ostream& outlog)
{
    outlog << "ScopeTable # "+ to_string(unique_id) << endl;

    //iterate through the current scope table and print the symbols and all relevant information
    for (int i=0; i<bucket_count; i++)
    {
        if (table[i].size()>0)
        {
            outlog << i << " --> " << endl;

            list<symbol_info*>::iterator it;

            for (it=table[i].begin(); it!=table[i].end(); it++)
            {
                symbol_info*sym=*it;

                outlog << "< " << sym->getname() << " : " << sym->get_type() <<" >" <<endl;

                if (sym->get_symbol_type()== "Function")
                    outlog << "Function Definition" << endl;
                else
                    outlog << sym->get_symbol_type() << endl;

                if (sym->get_symbol_type()=="Variable")
                {
                    outlog << "Type: " << sym->get_data_type() << endl;
                }

                else if (sym->get_symbol_type()=="Array")
                {
                    outlog << "Type: " << sym->get_data_type() << endl;
                    outlog << "Size: " << sym->get_array_size() << endl;
                }

                else if (sym->get_symbol_type()=="Function")
                {
                    outlog << "Return Type: " << sym->get_return_type() << endl;
                    outlog << "Number of Parameters: " << sym->get_param_count() << endl;
                    outlog << "Parameter Details: " << sym->get_param_details() << endl;
                }

                outlog << endl;

            }            
        }
    }

    outlog << endl;

}

//deleting the scope table after use
scope_table::~scope_table()
{
    for (int i=0; i<bucket_count; i++)
    {
        list<symbol_info*>::iterator it;

        for (it=table[i].begin(); it!=table[i].end(); it++)
        {
            delete (*it);
        }

        table[i].clear();
    }
}