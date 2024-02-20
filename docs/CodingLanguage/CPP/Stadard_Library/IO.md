## IO类

- IO对象无赋值无拷贝
![alt text](images/custom-image.png)

### 条件状态

![alt text](images/custom-image-2.png)

#### 流的状态

`iostate`类型
![alt text](images/custom-image-3.png)

- 可以利用`good() fail()`判断整体流的状态

### 管理缓冲

!!! note "刷新缓冲的原因"
    ![alt text](images/custom-image-4.png)
    <span class="box box-yellow">操纵符</span>

    ![alt text](images/custom-image-5.png)
    ```Cpp
    cout << unitbuf;   // 所有cout操作之后都刷新buffer
    cout << nounitbuf;
    ```

**流的关联操作**

```c++
cin.tie(&cout);
// old_tie指向的是cin的关联流；转化后，cin不再关联
ostream *old_tie = cin.tie(nullptr);
cin.tie(&cerr);
cin.tie(old_tie);
```

## File

![alt text](images/custom-image-6.png)

```cpp
ifstream in;
ofstream out;
string filename("CppLearning");
in.open(filename + ".md");
if (in)
{ //...
}
in.close();
```

### 文件模式

![alt text](images/custom-image-7.png)
"../Stadard_Library/关联容器.md"
!!! note "注意"
    以`out`方式打开文件，默认会覆盖
    ```cpp
    ofstream out("filename",mode);
    ofstream out("filename",ofstream::app | ofstream::out);

    ```

## String

![alt text](images/custom-image-8.png)

!!! example "Example"
    使用`istringstream`读取，ostringstream输入
    使用`ostringstream`可以在适当的时机输出所有值
    ```c++ hl_lines="7 10 12" title="istringstream"
    string str, line;
    vector<PersonInfo> People;
    while (getline(cin, line))
    {
        PersonInfo Person;
        string name, numbers;
        istringstream iStr(line);
        iStr >> name;
        Person.name = name;
        while (iStr >> numbers)
        {
            Person.Phones.push_back(numbers);
        }
        People.push_back(Person);
    }
    // print
    for (auto person : People)
    {
        cout << "name:" << person.name << endl;
        cout << "phones:" << endl;
        for (auto phone : person.Phones)
            cout << phone << endl;
    }
    ```


