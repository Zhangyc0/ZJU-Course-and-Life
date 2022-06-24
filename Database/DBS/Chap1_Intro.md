DBMS：**DB** + A set of programs used to access, update and manage the data in database.



|      |                                                              |
| ---- | ------------------------------------------------------------ |
| DDL  | DDL比DML要多，主要的命令有CREATE、ALTER、DROP等，DDL主要是用在定义或改变表（TABLE）的结构，数据类型，表之间的链接和约束等初始化工作上，他们大多在建立表时使用 |
| DML  | 它们是SELECT、UPDATE、INSERT、DELETE，就象它的名字一样，这4条命令是用来对数据库里的数据进行操作的语言 |
| DCL  | 是数据库控制功能。是用来设置或更改数据库用户或角色权限的语句，包括（grant,deny,revoke等）语句。在默认状态下，只有sysadmin,dbcreator,db_owner或db_securityadmin等人员才有权力执行 |



> List six major steps that you would take in setting up a database for a particular enterprise.

1. Analyse the purpose of this entreprise's setting up a database, figure out the data, operations the DB needed and its application.
2. Design the high-level description of data, define the relations of data using certain model.
3. Design its logical database scheme based on the conceptual design.
4. Refine the relations to fit the real situation.
5. Design the physical schema, like indexing, clustering.
6. Create the database, import the initial data, set users' groups and permission, test.



> List four significant **differences** between a **file-processing system** and a **DBMS**.

1. File-processing system may have some files that have different formats by different users that are independent to each others in one system, but a DBMS can avoid such inconsistency due to its atomicity.
2. File-processing system provides only physical schema to access data, but a DBMS provided not only physical but logical access to data.
3. File-processing system is often hierarchic, but a DB is often based on relation.



> Explain the concept of physical data independence, and its importance in database systems.

**Concept**

The ability to modify the physical schema without changing the logical shema.

**Importance**

It can ensure API only depends on the logical schema and won't be effected by the change of physical schema.



>What are five main functions of a database administrator?

1. Schema definition
2. Storage structure and access method definition
3. Schema and physical organization modification
4. Granting of authorization for data access
5. Routing maintenance