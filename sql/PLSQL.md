#PL/SQL简介
![](${currentFileDir}/images/20230418193621.png)
声明部分、执行部分、异常处理部分
![](${currentFileDir}/images/20230418193728.png)
![](${currentFileDir}/images/20230418194035.png)
```sql
DECLARE 
    v_sno VARCHAR2(10) :='04001';
    v_cno VARCHAR2(10) :='001';
    v_grade NUMBER :=90;
BEGIN 
    INSERT INTO SC VALUES (v_sno,v_cno,v_grade);
    CONNIT;
END;
```
![](${currentFileDir}/images/20230418194357.png)
练习实例
```sql
DECLARE 
    m sc.sno%type;
    n sc.cno%type;
    t sc.grade%type;//没有必要提前知道数据列的数据类型
BEGIN 
    m='04001';
    n='001';
    t='90';

    INSERT 
    INTO SC 
    VALUES (m,n,t);
    CONNIT;
END;
```
![](${currentFileDir}/images/20230418194836.png)

```sql
DECLARE 
    m sc.sno%rowtype;
BEGIN 
    m.sno='04002';
    m.cno='001';
    m.grade='91';
    INSERT 
    INTO SC 
    VALUES (m.sno,m.cno,m.grade);
    CONNIT;
END;
```

##运算符与表达式
###一般运算符
![](${currentFileDir}/images/20230418195101.png)
关系符号作用：调用存储过程中为形参赋值

###关系运算符
![](${currentFileDir}/images/20230418195300.png)

###逻辑运算符
![](${currentFileDir}/images/20230418195329.png)

###流程控制语句
![](${currentFileDir}/images/20230418195354.png)
####条件语句
![](${currentFileDir}/images/20230418195457.png)

```sql
DECLARE 
    m sc.grade%type;
BEGIN 
    select grade into m
    from sc
    where sno ='04001' and cno = '005';
    if m<60 then
        dbms_output.put_line(‘不及格’);
    elsif m>=60 and m<80 then
        dbms_output.put_line(‘及格’);
    elsif m>=80 and m<90 then
        dbms_output.put_line(‘良好’);
    else
        dbms_output.put_line(‘优秀’);
    end if;
END;
```
####循环语句
![](${currentFileDir}/images/20230418200333.png)
![](${currentFileDir}/images/20230418200515.png)

#游标
![](${currentFileDir}/images/20230418201105.png)
声明游标
![](${currentFileDir}/images/20230418201141.png)
打开游标
![](${currentFileDir}/images/20230418201312.png)
提取游标数据
移动游标指针
![](${currentFileDir}/images/20230418201359.png)
```sql
DECLARE 
    a varchar2(10);
    b varchar2(20);
    c varchar2(40);
    d number;
    m number;
    cursor c is select s.sno,sname,cname,grade;
        from s,sc,c
        where s.sno=sc.sno and c.cno=sc.cno and college='信息'; 
BEGIN 
    open c1;
    loop
        fetch c1 into a,b,c,d;
        exit when c1%notfound;
        if(d>60)then
            m:=m+d;
            dbms_output.put_line(a||b||c||d||m);
        end if;
    end loop;
    close c1;
END;
```
![](${currentFileDir}/images/20230418202808.png)
![](${currentFileDir}/images/20230418202835.png)
![](${currentFileDir}/images/20230418202851.png)
![](${currentFileDir}/images/20230418202912.png)
![](${currentFileDir}/images/20230418203304.png)

#存储过程
![](${currentFileDir}/images/20230418203537.png)
![](${currentFileDir}/images/20230418203550.png)
![](${currentFileDir}/images/20230418203809.png)

```sql
DECLARE 
    a varchar2(10);
    b varchar2(20);
    c varchar2(40);
    d number;
    m number;
    cursor c is select s.sno,sname,cname,grade;
        from s,sc,c
        where s.sno=sc.sno and c.cno=sc.cno and college='信息'; 
BEGIN 
    open c1;
    loop
        fetch c1 into a,b,c,d;
        exit when c1%notfound;
        if(d>60)then
            m:=m+d;
            dbms_output.put_line(a||b||c||d||m);
        end if;
    end loop;
    close c1;
END;