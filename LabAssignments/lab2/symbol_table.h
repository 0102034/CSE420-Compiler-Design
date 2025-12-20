#include "scope_table.h"

extern ofstream outlog;

class symbol_table
{
private:
    scope_table *current_scope;
    int bucket_count;
    int current_scope_id;

public:
    symbol_table(int bucket_count); //this needs to be done
    ~symbol_table();
    void enter_scope();
    void exit_scope();
    bool insert(symbol_info* symbol);
    symbol_info* lookup(symbol_info* symbol);
    void print_current_scope();
    void print_all_scopes(ostream& outlog);

    // you can add more methods if you need 
};

// complete the methods of symbol_table class
symbol_table::symbol_table(int bucket_count)
{
    this->bucket_count = bucket_count;
    this->current_scope_id = 0;
    this->current_scope = NULL;

    enter_scope();
}

symbol_table::~symbol_table()
{
    while (current_scope != NULL)
    {
        scope_table *temp = current_scope;
        current_scope = current_scope->get_parent_scope();
        delete temp;
    }
}

// creating new scope-> child new scope and the curr being the parent
void symbol_table::enter_scope()
{
    current_scope_id++;
    scope_table*new_scope = new scope_table(bucket_count, current_scope_id, current_scope);
    current_scope = new_scope;

    outlog << "New ScopeTable with ID " << current_scope_id << " created" << endl << endl;
}

// escape curr scope
void symbol_table::exit_scope()
{
    if (current_scope == NULL)
    {
        return;  //nowhere(scope) to go(exit)
    }
    outlog << endl << "Scopetable with ID " << current_scope->get_unique_id() << " removed" << endl << endl;
    //run back to parent table (now the current)
    scope_table *temp = current_scope;
    current_scope = current_scope->get_parent_scope();
    delete temp; //delete the prev one
}

//adding a neeeeew symbol to currrent scope
bool symbol_table::insert(symbol_info* symbol)
{
    if (current_scope == NULL)
    {
        return false; //scope nai
    }
    return current_scope->insert_in_scope(symbol);
}

// search for a symbol on the table if not go to the parentttt
 symbol_info* symbol_table::lookup(symbol_info* symbol)
{
    scope_table *temp = current_scope;

    while (temp != NULL)
    {
        symbol_info *found = temp->lookup_in_scope(symbol);
        if (found != NULL)
        {
            return found;
        }
        temp = temp->get_parent_scope();
    }
    return NULL; //non existance in every scope
}

void symbol_table::print_current_scope()
{
    if (current_scope != NULL)
    {
        current_scope->print_scope_table(cout);
    }
}

void symbol_table::print_all_scopes(ostream& outlog)
{
     outlog<<"################################"<<endl<<endl;
     scope_table *temp = current_scope;
     while (temp != NULL)
     {
         temp->print_scope_table(outlog);
         temp = temp->get_parent_scope();
     }
     outlog<<"################################"<<endl;
}