# String

!!! info "INFO"
    - [总结Blog](https://blog.csdn.net/weixin_45031801/article/details/136760767)

## 字符串分割

```c++
/*
s = "2024-1-2"
*/
Date AnalyDate(string s)
{
    stringstream ss(s);
    string line;
    vector<string> lines;
    while (getline(ss, line, '-'))
        lines.push_back(line);
    Date date;
    date.SetDate(stoi(lines[0]), stoi(lines[1]), stoi(lines[2]));
}
```

