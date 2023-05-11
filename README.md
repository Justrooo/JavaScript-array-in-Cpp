# JavaScript-array-in-Cpp
Array template class that is just a vector but with some cool functions directly taken from JavaScript's array. (Higher order functions from Array in js not included!)

[Here](https://github.com/Asabeneh/30-Days-Of-JavaScript/blob/master/05_Day_Arrays/05_day_arrays.md) is a documentation of most of the functions.

## Non-Js functions

### Overloaded << operator
<< operator simply prints out an Array in JavaScript's style. Here's an example:
```cpp
Array<int> arr {1, 2, 3, 4, 5};
cout << arr << endl;
```
Output:
```
[ 1, 2, 3, 4, 5 ]
```
However, if you do not wish this global << operator you can change the defined value COUT_OPERATOR from true to false in Array.h, line 7.
