# JavaScript-array-in-Cpp
Array template class that is just a vector but with some cool functions directly taken from JavaScript's array. (Higher order functions from Array in js not included!)

[Here](https://github.com/Asabeneh/30-Days-Of-JavaScript/blob/master/05_Day_Arrays/05_day_arrays.md) is a documentation of most of the functions.

## Non-JavaScript functions

### Constructors
You can declare an Array in four ways.
1. Default constructor
```cpp
// Syntax
Array<type> name;
// Example
Array<int> array; // []
```
2. Based on std::vector
```cpp
// Syntax
Array<type> name = vector_object; // Array<type> name = {vector_object}; or Array<type> name {vector_object};

// Example
vector<double> vector {9.81, 3.14, 74.2, 4.5};
Array<double> array = vector; // [ 9.81, 3.14, 74.2, 4.5 ]
```
3. Basen on initializer_list
```cpp
// Syntax
Array<type> name {value1, value2, value3 ...};

// Example
Array <char> abcdef {'a', 'b', 'c', 'd', 'e', 'f'}; // [ a, b, c, d, e, f ]
```
4. Repeated value n times
```cpp
// Syntax
Array<type> name(n, value);

// Example
Array<string> names(5, "My name here"); // [ My name here, My name here, My name here, My name here, My name here ]
```

### Overloaded "<<" operator
"<<" operator simply prints out an Array in JavaScript's style. Here's an example:
```cpp
Array<int> arr {1, 2, 3, 4, 5};
cout << arr << endl;
```
Output:
```
[ 1, 2, 3, 4, 5 ]
```
However, if you do not wish this global << operator you can change the defined value COUT_OPERATOR from true to false in Array.h, line 7.

### Overloaded "+" operator
"+" operator does the same job as Array::concat() function which appends one array into another. Example use:
```cpp
Array<int> arr{ 1, 2, 3, 4, 5 };
Array<int> arr2{ 6, 7, 8, 9, 10 };
cout << arr + arr2 << std::endl; // Concatenate (add) two arrays
```
Output:
```
[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]
```

### Getting the length (size) of an Array
In JavaScript if you have an Array you can use length variable. Howerever I made it a function so that you cannot modify the length of an Array. So in JavaScript it looks like this:
```js
array.length
```
But here it looks like this:
```cpp
array.length(); // Returns size of an Array
```

## For range loop
You can use for range loop to iterate through an Array like this:
```cpp
Array<int> fib {1, 1, 2, 3, 5, 8, 13};
int i{};
for (auto value : fib)
{
    cout << i++ << ") " << value << endl;
}
```
Output:
```
0) 1
1) 1
2) 2
3) 3
4) 5
5) 8
6) 13
```

## Initializer_list instead of multiple argument in functions splice(), push(), unshift()
I'll finish the rest of documentation tommorow
