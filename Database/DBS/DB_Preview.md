# Terminology

* tuple：行
* attribute属性：列
* 码
    * superkey超码：一个或多个属性的**集合**，可以唯一地区分不同的元组
    * candidate key候选码：任意真子集都不是超码，如`{ID}, {name, dept_name}`是，而`{ID, name}`不是候选码
    * primary key主码：人为选出用来区分元组的候选码



关系代数


| name | Symbol | Ex |    |
| --- | --- | --- | --- |
|  选择<br />select  | $\sigma$ | $\sigma_{\rm{salary \geqslant 85000}}(instructor)$ |    |
|  投影<br />project  | $\Pi$ | $\Pi_{ID,salary}(instructor)$ |    |
|  自然连接<br />join  | $\Join$$\bowtie$ | $instructor \Join department$ |    |
| 笛卡尔积 | $\times$ | $instructor \times department$ |    |
| 并 | $\cup$ | $\Pi_{name}(instructor) \cup \Pi_{name}(student)$ |    |
| Rename |  |  | |

# SQL

## 变量

### 类型

* char(n)
* varchar(n)
* int
* smallint
* numeric(p,d)：p位定点数，其中小数点右边有d位
* real, double：单双精度浮点数
* float(n)：精度至少为n的浮点数

## 操作

### 创建

### 查询

#### select..from...where

查询属性(输出是列

可以使用代数运算改变返回值，但是不改变数据库中数值

`select distinct attribute`可去除重复

多关系**自然连接**

```sql
-- 找出大学所有讲师的姓名及课程代号
select name, course_id
from instructor, teaches
where instructor.ID = teaches.ID
-- or use `natural join`
select name, course_id
from instructor natural join teaches

-- Normal Form
select A1, A2, ..., An
from E1, E2, ..., En;
-- 其中Ei是单个关系或多个关系的自然连接
```

注意属性重复

另一个例子：找出教师和他们所讲授课程的名字

```sql
-- 正确
select name, title
from instructor natural join teaches, course
where teaches.course_id = course.course_id;

-- 错误
select name, title
from instructor natural join teaches natural join course;
-- instructor ⋈ teaches与course的共有属性除了course_id还有dept_name，这种方式要求两者均相等，因此会忽略“课程不是任课教师所在系开的”的情况
```

### 附加的基本运算

#### 更名

改属性名

`old_name as new_name`

改关系名

```sql
-- 便于查询
select T.name, S.course_ID
from instructor as T, teaches as S
where T.ID = S.ID;
```

#### 字符串运算

* `'abc'`表示字符串，若有字符串中有单引号，则用`'abc''def'`表示"abc'def"

* Case Sensitive 可以在数据库属性中修改

* `upper()`, `lower()`, `trim()`(去掉字符串后面的空格)

* 字符串匹配$\begin{cases} \rm \% & 任意字符串 \\ \rm \_ & 任意字符 \end{cases}$

    * 例如吗， 吗， 吗， 

        ```sql
        select dept_name
        from department
        where building like "ZJG%";	-- 找到办公楼在紫金港的系的名字
        ```

    * 定义转义字符

        `like 'ab\%cd%' escape '\'`：以"ab%cd"开头的字符串

        `like 'ab\\cd%' escape '\'`：以"ab\cd"开头的字符串

#### where的谓词运算

* 元组、字典序

### 集合运算

`union`, `intersect`, `except`自动去重

\+ `all` 表示不去除重复

### 空值

arithmetic：涉及`null`结果为`null`

logical：涉及`null`结果为`unknown`

### 聚集函数

> 以集合为输入，输出单个数值

`min, avg, max, sum, count`

其中`sum`和`avg`的输入必须为数字集



**group by**：使聚集函数作用在一组元组集而不是单个元组集上

> 通过给出属性来构造分组

Ex. 计算每个系的平均工资

```sql
select dept_name, avg(salary) as avg_salary
from instructor
group by dept_name;	-- 按dept_name属性进行分组
```

**having**：增加对分组的限定条件

Ex. 只考虑平均工资超过10000的系

```sql
select dept_name, avg(salary) as avg_salary
from instructor
group by dept_name	-- 按dept_name属性进行分组
having avg(salary) > 100000;
```

**对空值**：除count以外的聚集函数均不考虑`null`；特殊的，若输入集为空集，`count`返回值为0，其他返回值为`null`



### 嵌套

#### 集合成员资格

> 利用`in`和`not in`进行

Ex. 查出2009秋+2010春开课的课程集合，除了用3个`and`还可以

```sql
select distinct course_id
from section
where semester = 'Fall' and year = 2009 and
	course_in in (select course_id
                  from section
                  where semester = 'Spring' and year = 2010);
```

#### 集合的比较

> 用`> some`, `<= all`等进行判断

Ex. 找出平均工资最高的系

```sql
...
...
group by dept_name
having avg(salary) >= all (select avg(salary)	-- >=包括了自己
                           from instructor
                           group by dept_name);
```

#### 空关系测试

> 利用`exists`查询结果中是否存在<u>元组</u>

Ex. 还是查出2009秋+2010春开课的课程集合

```sql
select distinct course_id
from section as S
where semester = 'Fall' and year = 2009 and
	exists (select *	-- *表示属性全选？
            from section as T
            where semester = 'Spring' and year = 2010 and
            	S.course_id = T.course_id);
```

#### 重复元组存在性测试

unique

#### 嵌套在from子句中的查询

#### with定义临时关系

写在`select`之前，仅对包含`with`的查询有效

#### 标量子查询



### 修改

#### 删除元组

```sql
delete from r
where P;

---

delete from instructor
where dept_name in (select dept_name	-- 删除在Watson楼工作的系的教师的元组
                    from department
                    where building = 'Watson');
```

#### 插入元组

insert into

#### 更新属性

```sql
update relation
set attribute = ...
where P;

---

update relation
set attribute = case
		when P then ...
		else ...
	end;

```

