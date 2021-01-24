# Csv Parser

Парсер для CSV файлов, реализованный через класс с перегруженным
оператором индексирования. Для хранения ячеек разных типов используется
std::tuple.

### Примеры работы

<hr style="height:1px">

**file1.csv**
```
20,15,Simple string,4.2
12,44,Not so! simple string,0.4
09,60,Not so! simple string,7.8
```
**out**
```
[20, 15, Simple string, 4.2]
[12, 44, Not so! simple string, 0.4]
[9, 60, Not so! simple string, 7.8]
```

<hr style="height:1px">

**file2.csv**
```
01,0,,4.2
12,4,str"ing,0.4
09,60,string,7.8
```
**out**
```
[1, 0, , 4.2]
Line 2: Unexpected exit symbol.
```

<hr style="height:1px">

**file3.csv**
```
100000000,100000,string,40.0
10000000000000000,100000,string,40.0
35,11,,40.0
```
**out**
```
[100000000, 100000, string, 40]
Line 2: Wrong field type.
```