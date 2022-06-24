# Obeject

**create type**

**not final**：可继承

**method**：内联函数，先声明后定义

**Inheritance**：create type xxx under xxx

**array**： author-array varchar(20) array[10]， 定长，可随机访问，有顺序(区分一二三作)

**multiset**： keyword-set varchar multiset，不定长，不可随机访问(没有顺序)

**unnest**：将嵌套结构(如array、mset)解为序列使用，是不带顺序的，如果要顺序则需要**with ordinality**

**ref**：给出对象id，ref using varchar(20)      ref is person_id user generated

# O-R

