#include "Class_Vector.h"

int max_in_use(int n1, int n2){
    if (n1 > n2) return n1;
    return n2;
}

char or_comparison(char c1, char c2){
    if ((c1 == '0' && c2 == 'x') || (c2 == '0' && c1 == 'x')) return 'x';
    if ((c1 == '1' && c2 == 'x') || (c2 == '1' && c1 == 'x') || (c1 == '0' && c2 == '1') || (c2 == '0' && c1 == '1') || (c1 == '1' && c2 == '1')) return '1';
    return '0';
}

char and_comparison(char c1, char c2){
    if ((c1 == '1' && c2 == 'x') || (c2 == '1' && c1 == 'x')) return 'x';
    if ((c1 == '0' && c2 == 'x') || (c2 == '0' && c1 == 'x') || (c1 == '0' && c2 == '0') || (c1 == '0' && c2 == '1') || (c2 == '0' && c1 == '1')) return '0';
    return '1';
}

char not_operation(char c){
    if (c == '1') return '0';
    if (c == '0') return '1';
    return 'x';
}

Vector get_res_vector (Vector first, Vector second){
    int max = max_in_use(first.in_use, second.in_use);
    first.add_x(max);
    second.add_x(max);
    Vector res(max);
    return res;
}

Vector OR(Vector first, Vector second){
    Vector res = get_res_vector(first, second);
    int max = max_in_use(first.in_use, second.in_use);
    for (int i = 0; i < max; i++) res.array[i] = or_comparison(first.array[i], second.array[i]);
    return res;
}

Vector AND(Vector first, Vector second){
    Vector res = get_res_vector(first, second);
    int max = max_in_use(first.in_use, second.in_use);
    for (int i = 0; i < max; i++) res.array[i] = and_comparison(first.array[i], second.array[i]);
    return res;
}

Vector::Vector (){
    in_use = 0;
    for (char & i : array) i = '0';
}

Vector::Vector (int n){
    if (n > MAX_SIZE) n = MAX_SIZE;
    in_use = n;
    for (int i = 0; i < in_use; i++) array[i] = 'x';
    for (int i = in_use; i < MAX_SIZE; i++) array[i] = '0';
}

Vector::Vector (const string& str){
    int i;
    for (i = 0; i < str.length() && i < MAX_SIZE; i++){
        if (str[i] == '0' || str[i] == '1') {
            array[i] = str[i];
        } else array[i] = 'x';
    }
    in_use = i;
    for (; i < MAX_SIZE; i++) array[i] =  '0';
}

void Vector::set_array(const string& str){
    int i;
    for (i = 0; i < str.length() && i < MAX_SIZE; i++){
        if (str[i] == '0' || str[i] == '1') {
            array[i] = str[i];
        } else array[i] = 'x';
    }
    in_use = i;
    for (; i < MAX_SIZE; i++) array[i] =  '0';
}

void Vector::get_array(){
    for (int i = 0; i < in_use; i++) cout << array[i];
    cout << endl << in_use << endl;
}

Vector Vector::NOT(){
    Vector res(in_use);
    for (int i = 0; i < in_use; i++) res.array[i] = not_operation(array[i]);
    return res;
}

bool Vector::certainty(){
    for (int i = 0; i < in_use; i++) if (array[i] == 'x') return false;
    return true;
}

void Vector::add_x(int new_in_use) {
    for (int i = in_use; i < new_in_use; i++) array[i] = 'x';
    in_use = new_in_use;
}

int Vector::get_in_use() const{
    return in_use;
}

char Vector::get_array_i(int i){
    return array[i];
}

void Vector::set_array_i(int i, char c) {
    array[i] = c;
}

char eq (char c1, char c2) {
    if ((c1 == '1' && c2 == '1') || (c1 == '0' && c2 == '0')) return '1';
    if ((c1 == '0' && c2 == '1') || (c2 == '0' && c1 == '1')) return '0';
    return 'x';
}

char more (char c1, char c2) {
    if (c1 == '0' && c2 == '1' || c1 == '0' && c2 == '0' || c1 == '1' && c2 == '1') return '0';
    if (c1 == '1' && c2 == '0') return '1';
    return 'x';
}

char less_ (char c1, char c2) {
    if (c1 == '1' && c2 == '0' || c1 == '0' && c2 == '0' || c1 == '1' && c2 == '1') return '0';
    if (c1 == '0' && c2 == '1') return '1';
    return 'x';
}

char more_eq (char c1, char c2) {
    if (c1 == 'x' && c2 == '1' || c1 == '0' && c2 == 'x') return 'x';
    if (c1 == '0' && c2 == '1') return '0';
    return '1';
}

char less_eq (char c1, char c2) {
    if (c1 == 'x' && c2 == '0' || c1 == '1' && c2 == 'x') return 'x';
    if (c1 == '1' && c2 == '0') return '0';
    return '1';
}

Vector comparison (Vector first, Vector second, const string& op) {
    Vector res = get_res_vector(first, second);
    if (op == "="){
        for (int i = 0; i < first.get_in_use(); i++) {
            res.set_array_i(i, eq(first.get_array_i(i), second.get_array_i(i)));
        }
    }
    if (op == ">"){
        for (int i = 0; i < first.get_in_use(); i++) {
            res.set_array_i(i, more(first.get_array_i(i), second.get_array_i(i)));
        }
    }
    if (op == "<"){
        for (int i = 0; i < first.get_in_use(); i++) {
            res.set_array_i(i, less_(first.get_array_i(i), second.get_array_i(i)));
        }
    }
    if (op == ">="){
        for (int i = 0; i < first.get_in_use(); i++) {
            res.set_array_i(i, more_eq(first.get_array_i(i), second.get_array_i(i)));
        }
    }
    if (op == "<="){
        for (int i = 0; i < first.get_in_use(); i++) {
            res.set_array_i(i, less_eq(first.get_array_i(i), second.get_array_i(i)));
        }
    }
    return res;
}