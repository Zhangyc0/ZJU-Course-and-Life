```sql
select database();

show tables;

sp_password 'old' 'new' 'username'

case when()then when()then else end
```

join 只能用在from后面，不能用在where里

---

**where**: 后面不能接**聚合函数** ，可以接**单行函数**
单行函数:就是使用函数查询返回一条结果如（等于，时间转换，转换函数等）
聚合函数:就是使用函数查询返回多调数据的如（大于，小于，不等于）
**having**: <u>在group by 之后执行</u> 可以接聚合函数

“Where” 是一个约束声明，使用Where来约束来自[数据库](http://lib.csdn.net/base/mysql)的数据，Where是在结果返回之前起作用的，且Where中不能使用聚合函数。

“Having”是一个过滤声明，是在查询返回结果集以后对查询结果进行的过滤操作，在Having中可以使用聚合函数。

---

连接就四种：inner, left outer, right outer, full outer；加条件有三种方式 `natural` `on ...` `using (A1, ...)`

具体的看PPT3.100

~~注意，outer是在两个表某个共有属性不匹配时起作用，left outer会保留左表中的这些属性，右表中其他属性为null

---

```mysql
select * from card
where
    cno not in (select cno from borrow);
-- 这两个为什么返回结果不一样？
select * from card as C
where
    not exists (select cno from borrow as B
        where C.cno = B.bno);
```

---

后几章概念的关系：

可串行化

冲突可串

可恢复

死锁

级联回滚

---

