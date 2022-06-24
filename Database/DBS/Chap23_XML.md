[TOC]

==<!--考试有大题，去装软件-->==

# Structure

**Extensible**：tag可自定义，像html就不行

**Element **：由tag包起来的，可以嵌套其他Element

```xml
<!--right-->
<a>...<b>...</b>...</a>
<!--wrong-->
<a>...<b>...</a>...</b>

<!--可以加文本信息-->
<course>
    This course is being offered for the first timein 2009.<!--这个-->
    <course_id> BIO-399 </course_id>
    <title> Computational Biology </title>
    <dept_name> Biology </dept_name>
    <credits> 3 </credits>
</course>
```



## Attribute和Subelement

```xml
<!--Attribute-->
<course course_id= "CS-101">...</course>
<!--Subelement-->
<course>
    <course_id>CS-101</course_id>
    ...
</course>
```

## Namespace

因为同名但语义不同(例如不同学校的学号格式不一样)的标签可能带来问题

Use keyword `xmlns`

```xml
<university xmlns:yale="http://www.yale.edu">	<!--声明yale，被定义为"http://www.yale.edu"(unique string)，作为标识符，防止tag冲突-->
    ...
    <yale:course>
        <yale:course_id> CS-101 </yale:course_id>
        <yale:title> Intro. to Computer Science</yale:title>
        <yale:dept_name> Comp. Sci. </yale:dept_name>
        <yale:credits> 4 </yale:credits>
    </yale:course>
    ...
</university>
```

## Other Syntax

**< />**

```xml
<!--使用`/>`且没有subelement且没有text content可以不用end tag-->
<course  course_id="CS-101" Title="Intro. To Computer Science" dept_name = "Comp. Sci." credits="4"  />
```

**CDATA**

因为在元素中"<"(新元素的开始)和"&"(字符实体的开始)是非法的

```xml
<!--使用`<![CDATA[]]>`(char data)-->
<script>
<![CDATA[
function matchwo(a,b) {
    if (a < b && a < 0) then {
        return 1;
    }
    else {
        return 0;
    }
}
]]>
</script>


<![CDATA[<course> … </course>]]>
```

**转义**

| `&lt;`   | &lt;   | 小于   |
| -------- | ------ | ------ |
| `&gt;`   | &gt;   | 大于   |
| `&amp;`  | &amp;  | 和号   |
| `&apos;` | &apos; | 省略号 |
| `&quot;` | &quot; | 引号   |



# XML Document Schema

为了限制XML中的信息而定义的

Two mechanisms for specifying XML schema

* Document Type Definition (DTD)
    * Widely used
* XML Schema 
    * Newer, increasing use

## DTD syntax

* DTD constraints structure of XML data
    * What elements can occur
    * What attributes can/must an element have
    * What subelements can/must occur inside each element, and how many times.
* DTD does not constrain data types
    * All values represented as strings in XML

```dtd
<!ELEMENT element (subelements-specification) >
<!ATTLIST element (attributes)  >
```



```dtd
<!--Example-->
<!ELEMENT department (dept_name  building, budget)>
<!ELEMENT dept_name (#PCDATA)>
<!ELEMENT budget (#PCDATA)>
<!--Regex-->
<!ELEMENT university ( ( department | course | instructor | teaches )+)>
```

Regex Notation: 

*  " | "   -  alternatives
*  " + "  -  1 or more occurrences
*  " * "   -  0 or more occurrences
*  " ? "   -  0 or 1 occurrence

**ELEMNT**的可选类型声明(声明元素)

*  **PCDATA**：指的是被解析的字符数据（Parsed Character Data）
*  empty：空值
*  any：没有限制，是缺省值

Ex.

```dtd
<!DOCTYPE  university [
    <!ELEMENT university ( (department|course|instructor|teaches)+)>	<!--出现一或多次-->
    <!ELEMENT department ( dept_name, building, budget)>
    <!ELEMENT course ( course_id, title, dept name, credits)>
    <!ELEMENT instructor (IID, name, dept_name, salary)>
    <!ELEMENT teaches (IID, course_id)>
    <!ELEMENT dept_name( #PCDATA )>		<!--department、course、instructor的属性在这里-->
    <!ELEMENT building( #PCDATA )>		<!--department的属性在这里-->
    <!ELEMENT budget( #PCDATA )>		<!--department的属性在这里-->
    <!ELEMENT course_id ( #PCDATA )>	<!--course的属性在这里-->
    <!ELEMENT title ( #PCDATA )>		<!--course的属性在这里-->
    <!ELEMENT credits( #PCDATA )>		<!--course的属性在这里-->
    <!ELEMENT IID( #PCDATA )>
    <!ELEMENT name( #PCDATA )>
    <!ELEMENT salary( #PCDATA )>
]>
```

**ATTILIST**

* 可选类型声明(声明属性)
    * CDATA
        * 包含字符数据
    * ID
        * 一个ELEMENT最多只有一个并且是unique的
        * 可以作为object identifier
    * IDREF
        * 表示该ATTI是对一个ELEMENT的引用(通过该ELEMENT的ID的形式表示)，must contain the ID value of an element in the same document
    * IDREFS
        * contains a set of (0 or more) ID values.  Each ID value must contain the ID value of an element in the same document
        * sep by space
* Whether
    * mandatory (#REQUIRED)
    * has a default value (value)
    * or neither (#IMPLIED)

Ex.

```dtd
<!ATTLIST course course_id CDATA #REQUIRED>
<!ATTLIST course
    course_id	ID		#REQUIRED
    dept_name	IDREF	#REQUIRED
    instructors	IDREFS	#IMPLIED	<!--可能有多个老师上一门课-->
>
```

Ex2.

```dtd
<!DOCTYPE university-3 [
    <!ELEMENT university ( (department|course|instructor)+)>
    <!ELEMENT department (building, budget)>
    <!ATTLIST department
        dept_name ID #REQUIRED >
    <!ELEMENT course (title, credits)>
    <!ATTLIST course
        course_id ID #REQUIRED			<!--ID-->
        dept_name IDREF #REQUIRED		<!--IDREF-->
        instructors IDREFS #IMPLIED >	<!--IDREFS-->
    <!ELEMENT instructor ( name, salary )>
    <!ATTLIST instructor
        IID ID #REQUIRED 
        dept_name IDREF #REQUIRED >
    · · · declarations for title, credits, building, budget, name and salary · · ·
]>
```

Ex3. XML data with ID and IDREF attributes

```xml
<university-3>
       <department dept name="Comp. Sci.">
               <building> Taylor </building>
               <budget> 100000 </budget>
       </department>
       <department dept name="Biology">
               <building> Watson </building>
               <budget> 90000 </budget>
       </department>
       <course course id="CS-101" dept name="Comp. Sci" instructors="10101 83821">
                <title> Intro. to Computer Science </title>
                <credits> 4 </credits>
       </course>
       ….
       <instructor IID="10101" dept name="Comp. Sci.">
                <name> Srinivasan </name>
                <salary> 65000 </salary>
       </instructor>
       ….
</university-3>
```

### Limitations

* No typing of text elements and attributes
    * All values are strings, no integers, reals, etc.
* Difficult to specify unordered sets of subelements
    * Order is usually irrelevant in databases (unlike in the document-layout environment from which XML evolved)
    * `(A | B)*` allows specification of an **unordered** set, but cannot ensure that each of A and B occurs <u>only once</u>
* IDs and IDREFs are untyped
    * The instructors attribute of an course may contain a reference to another course, which is meaningless
        * instructors attribute should ideally be constrained to refer to instructor elements

## XML Schema

* XML Schema is a more sophisticated schema language which addresses the drawbacks of DTDs.  Supports
    * Typing of values
        * E.g. integer, string, etc
        * Also, constraints on min/max values
    * User-defined, comlex types
    * Many more features, including
        * uniqueness and foreign key constraints, inheritance 
* XML Schema is itself specified in XML syntax, unlike DTDs (DTD并不是XML语法的，你看放到代码框里都没高亮，放到vscode也疯狂报错)
    * More-standard representation, but verbose
* XML Scheme is integrated with namespaces 
* BUT:  XML Schema is significantly more complicated than DTDs.

```xml
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">
    <xs:element name="university" type="universityType" />
    <xs:element name="department">
        <xs:complexType>
            <xs:sequence>
                <xs:element name="dept name" type="xs:string" />
                <xs:element name="building" type="xs:string" />
                <xs:element name="budget" type="xs:decimal" />
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="course">
        <xs:element name="course id" type="xs:string" />
        <xs:element name="title" type="xs:string" />
        <xs:element name="dept name" type="xs:string" />
        <xs:element name="credits" type="xs:decimal" />
    </xs:element>
    <xs:element name="instructor">
        <xs:complexType>
            <xs:sequence>
                <xs:element name="IID" type="xs:string" />
                <xs:element name="name" type="xs:string" />
                <xs:element name="dept name" type="xs:string" />
                <xs:element name="salary" type="xs:decimal" />
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="teaches">
        <xs:complexType>
            <xs:sequence>
                <xs:element name="IID" type="xs:string" />
                <xs:element name="course id" type="xs:string" />
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:complexType name="UniversityType">
        <xs:sequence>
            <xs:element ref="department" minOccurs="0" maxOccurs="unbounded" />
            <xs:element ref="course" minOccurs="0" maxOccurs="unbounded" />
            <xs:element ref="instructor" minOccurs="0" maxOccurs="unbounded" />
            <xs:element ref="teaches" minOccurs="0" maxOccurs="unbounded" />
        </xs:sequence>
    </xs:complexType>
</xs:schema>
```

**说明**

* Choice of “xs:” was ours - any other namespace prefix could be chosen
* Element “university” has type “universityType”, which is defined separately
    * <u>xs:complexType is used later to create the named complex type “UniversityType”</u>



**Attributes**

使用`:attribute`标签，`use = "required"`对应的DTD中`#REQUIRED`

**Key**

主键：`:key`，外键：`:keyref`

* Attr
    * `name`
    * (`refer`)
* Subelement
    * `selector`：定义约束范围
    * `field`：声明指定形成键的元素或属性

Ex.

```xml
<xs:key name = "deptKey">	<!--Key-->
    <xs:selector xpath = "/university/department"/>
    <xs:field xpath = "dept_name"/>
<\xs:key>
<xs:keyref name = "courseDeptFKey" refer="deptKey">  <!--Foreign Key-->
    <xs:selector xpath = "/university/course"/>
    <xs:field xpath = "dept_name"/>
<\xs:keyref>
```



# Query and transform

## Tree Model

* Query and transformation languages are based on a tree model of XML data
* An XML document is modeled as a tree, with nodes corresponding to elements and attributes
    * Element nodes have child nodes, which can be attributes or subelements
    * Text in an element is modeled as a text node child of the element
    * Children of a node are ordered according to their order in the XML document
    * Element and attribute nodes (except for the root node) have a single parent, which is an element node
    * The root node has a single child, which is the root element of the document

## querying/translation lang

以下部分使用的例子来自这个xml

```xml
<university-3>
    <department dept_name="Comp. Sci.">
        <building> Taylor </building>
        <budget> 100000 </budget>
    </department>
    <department dept_name="Biology">
        <building> Watson </building>
        <budget> 90000 </budget>
    </department>
    <course course_id="CS-101" dept_name="Comp. Sci" instructors="10101 83821">
        <title> Intro. to Computer Science </title>
        <credits> 4 </credits>
    </course>
    <course course_id="BIO-301" dept_name="Biology" instructors="76766">
        <title> Genetics </title>
        <credits> 4 </credits>
    </course>
    <instructor IID="10101" dept_name="Comp. Sci.">
        <name> Srinivasan </name>
        <salary> 65000 </salary>
    </instructor>
    <instructor IID="83821" dept_name="Comp. Sci.">
        <name> Brandt </name>
        <salary> 72000 </salary>
    </instructor>
    <instructor IID="76766" dept_name="Biology">
        <name> Crick </name>
        <salary> 72000 </salary>
    </instructor>
</university-3>
```

### XPath

用文件系统的表示方式来选择文档中的部分

Ex.

* 如`/university-3/instructor/name`返回值为整个元素，包括tag

    ```xml
    <name>Srinivasan</name>
    <name>Brandt</name>
    ```

* 不想要tag可以用`/university-3/instructor/name/text()`

* 要加条件可以用`[]`
    * `/university-3/course[credits >= 4]` returns course elements with a credits value greater than 4
    * `/university-3/course[credits]` returns course elements containing a credits subelement(有credits 就返回)
    * 支持布尔运算：`and` `or` `not()`

* 取属性用`@`

    * `/university-3/course[credits >= 4]/@course_id` returns the course identifiers of courses with credits >= 4
        * IDREF attributes are not dereferenced automatically

* 还有函数

    * `count()`
        * `/university-2/instructor[count(./teaches/course)> 2]` returns instructors teaching more than 2 courses (on university-2 schema)
    * `id()`
        * id() can also be applied to sets of references such as IDREFS and even to strings containing multiple references separated by blanks，解引用，拿属性值取回对应的元组
        * `/university-3/course/id(@dept_name)` returns <u>all **department** elements</u> referred to from the dept_name attribute of course elements.
    * `doc(name)`
        * returns the root of a named document

* 特殊操作符

    * `|`：并集
    * `//`：相当于跳级
        * `/university-3//name` finds any name element anywhere  under the /university-3 element, regardless of the element in which it is contained.
    * `*`：所有子节点
    * `..`：父节点   

### XQuery

Based on W3C 2005 Draft

格式更像shell和make这种上古描述性的而不是高级语言

**FLOWR**

* for
    * SQL from
    * 多于一个时是笛卡尔积
* let
    * 赋值(应该是引用而不是真赋值)，简化表达
* where
    * SQL where
* order by
    * SQL order by
* return
    * SQL select

```xquery
for $x in /university-3/course
let $courseId := $x/@course_id
where $x/credits > 3
return <course_id> { $courseId } </course_id>	<!--大括号表示里面是变量，否则返回值就是字符串的"$courseID"，但是整个返回值还是文本型的，所以tag也会被返回-->


for $x in /university-3/course[credits > 3]
return <course_id> { $x/@course_id } </course_id>


return element course_id { element  $x/@course_id } 
```

#### XQuery Syntax

##### Join

```xquery
<!--Joins are specified in a manner very similar to SQL-->
for $c in /university/course,
    $i in /university/instructor,
    $t in /university/teaches
where $c/course_id= $t/course id and $t/IID = $i/IID
return <course_instructor> { $c $i } </course_instructor>
<!--The same query can be expressed with the selections specified as XPath 9selections:-->
for $c in /university/course,
    $i in /university/instructor,
    $t in /university/teaches[ $c/course_id= $t/course_id and $t/IID = $i/IID]
return <course_instructor> { $c $i } </course_instructor>
```



##### Nested Query

```xquery
<university-1> 
{for $d in /university/department
    return <department>
        { $d/* }
        { for $c in /university/course[dept_name = $d/dept_name]
            return $c }
    </department>
}
{for $i in /university/instructor
    return  <instructor>
        { $i/* }
        { for $c in /university/teaches[IID = $i/IID]	<!--instructor下面的子元素-->
            return $c/course_id }
    </instructor>
}
</university-1>

<!--总的返回值-->
"<univrsity-1><department>d系的building和budget d系的所有课</department><instructor>i导师的name和salary i导师的所有课</instructor></university-1>"
```

<u>怎么个嵌套法？是直接笛卡尔积？是的</u>

##### Sort

The `order by` clause can be used at the <u>**end** of any expression</u>. 

```xquery
for $i in /university/instructor
order by $i/name
return <instructor> { $i/* } </instructor>
```

```xquery
<university-1> {
        for $d in /university/department
        order by $d/dept name
        return
             <department>
                 { $d/* }
                 { for $c in /university/course[dept name = $d/dept name]
                   order by $c/course id
                   return <course> { $c/* } </course> }
             </department>
      } </university-1>
<!--输出系和系的课，且先按系排序再按课排序-->
```



#### Function

* Types are optional for function parameters and return values
* The * (as in decimal*) indicates a sequence of values of that type
* Universal and existential quantification in where clause predicates
    * some \$e in path satisfies P
    * every \$e in path satisfies P
    * Add and fn:exists(\$e) to prevent empty \$e from satisfying every clause
* XQuery also supports If-then-else clauses

找到给定ID的老师所在的系开设的所有课程

```xquery
declare function local:dept_courses($iid as xs:string) 
          as element(course)* 
{
    for $i in /university/instructor[IID = $iid],
          $c in /university/courses[dept_name = $i/dept name]
    return $c
}
```



### XSLT

The **XML Stylesheet Language (XSL)** was originally designed for generating HTML from XML

**XSL** is a family of recommendations for defining XML document transformation and presentation. It consists of three parts:

* XSL Transformations (**XSLT**): a language for transforming XML 
* the XML Path Language (**XPath**): an expression language used by XSLT to access or refer to parts of an XML document. (XPath is also used by the XML Linking specification) 
* XSL Formatting Objects (**XSL-FO**): an XML vocabulary for specifying formatting semantics 

**XSLT** is a general-purpose transformation language. Can translate XML to XML, and XML to HTML using rules called **templates**

#### Template

template tag

* 属性
    * `match`：specifies a pattern in XPath
* 子元素
    * `value-of`：selects (outputs) specified values (here, customer_name)
        * 属性：`select`

```xaml
<xsl:template match="/bank-2/customer">
    <xsl:value-of select="customer_name" />
</xsl:template>

<xsl:template match="*" /> <!--matches all elements that **do not match** any other template-->
```

> 所有这个match*有什么用？？？？

##### Output

Ex. to wrap results in new XML elements？

```xml
<xsl:template match="/bank-2/customer">
    <customer>
        <xsl:value-of select="customer_name" />
    </customer>
</xsl:template>
<xsl:template match="*" />
<!--Output-->
<customer> Joe  </customer>
<customer> Mary </customer>
```

* Note: Cannot directly insert a `xsl:value-of` tag inside another tag
    * E.g. cannot create an attribute for `<customer>` in the previous example by directly using `xsl:value-of`(必须通过subelement，为什要这样设定？？)
    * XSLT provides a construct xsl:attribute to handle this situation
        * `xsl:attribute` adds attribute to the preceding element

##### Structural Recursion

Template action can apply templates recursively to the contents of a matched element

```xml
<xsl:template match="/bank">
    <customers>
        <xsl:template apply-templates />
    </customers>
</xsl:template>
<xsl:template match="/customer">
    <customer>
        <xsl:value-of select="customer_name" />
    </customer>
</xsl:template>
<xsl:template match="*" />

<!--Example output:-->
<customers>
    <customer> John </customer>
    <customer> Mary </customer>
</customers>
```



#### XSLT Syntax

##### Join

* XSLT keys allow elements to be looked up (indexed) by values of subelements or attributes

    * Keys must be declared (with a name) and, the key() function can then be used for lookup.  E.g. 

        ```xml
        <xsl:key name="acctno" match="account" use="account_number" />
        <xsl:value-of select= key("acctno" ,"A-101" )
        ```

* Keys permit (some) joins to be expressed in XSLT

    ```xml
    <xsl:key name="acctno" match="account" use="account_number" />
    <xsl:key name="custno" match="customer" use="customer_name" />
    <xsl:template match="depositor">
        <cust_acct>
            <xsl:value-of select= key("custno" ,"customer_name" ) />
            <xsl:value-of select= key("acctno" ,"account_number" ) />
        </cust_acct>
    </xsl:template>
    <xsl:template match="*" />
    ```

##### Sort



# API

两种

* SAX (Simple API for XML)
    * Based on parser model, user provides event handlers for parsing events 
        * E.g. start of element, end of element
        * Not suitable for database applications
* DOM (Document Object Model)
    * XML data is parsed into a tree representation 
    * Variety of functions provided for traversing the DOM tree
    * E.g.: Java DOM API provides Node class with methods

        ```java
        getParentNode(), getFirstChild(), getNextSibling()
        getAttribute(), getData() /*(for text node)*/
        getElementsByTagName(), ...
        ```

    * Also provides functions for updating DOM tree

# Storage of XML

* 非关系型
    * Plain Text
        * Natural for storing XML
        * But has all problems discussed in Chapter 1 (no concurrency, no recovery, …)
    * XML database
        * Database built specifically for storing XML data, supporting DOM model and declarative querying
        * Currently no commercial-grade systems
* 关系型
    * Data must be translated into relational form
    * Advantage: mature database systems
    * Disadvantages: overhead of translating data and queries(转换很麻烦)



## Storage in 关系DB

Alternatives:

* String Representation
* Tree Representation
* Map to relations

### String

\> 将Element都视作string，在rDB中将所有attr设为string类型的进行存储

* 只需要一张表
* 或者可以按类型分，一个类型一张表

\> 需要索引

* Store values of subelements/attributes to be indexed as extra fields of the relation, and build indices on these fields
    * E.g. `customer_name` or `account_number`
* Some database systems support **function indices**, which use the result of a function as the key value(获得特征，然后用Hash等方式更快地构件索引，但是如何提取特征是个难题)
    * The function should return the value of the required subelement/attribute

\> 好处

* Can store any XML data even without DTD
* As long as there are many top-level elements in a document, strings are small compared to full document
    * Allows fast access to individual elements.

\> 坏处

* 效率低：访问一个元素，得把整个元组的字符串提取出来，再转换字符串，再去找元素

### Tree



<img src="assets/image-20200416114950446.png" style="zoom: 33%;" />

\> 好处：不需要DTD也可以存任何数据

\> 坏处

* Data is broken up into too many pieces, increasing space overheads
* Even simple queries require a large number of **joins**, which can be slow(时间复杂度非常稳定，稳定的高)

### Mapping

**最有效的存储方式**

* Relation created for each **element** type whose schema is known:
    * An <u>id attribute</u> to store a unique id for each element
    * A <u>relation attribute</u> corresponding to each element attribute (存除了id以外的元素？)
    * A parent_id attribute to keep track of parent element
        * As in the tree representation
        * Position information (i^th^ child) can be stored too
* All subelements that occur only once can become relation attributes
    * For text-valued subelements, store the text as attribute value
    * For complex subelements, can store the id of the subelement (为什么要把复合元素也这么搞？)
* Subelements that can occur multiple times represented in a separate table (多个电话，拎到新表)
    * Similar to handling of multivalued attributes when converting E-R diagrams to tables

## Storage in 关系Sys

* Publishing: process of converting relational data to an XML format
* Shredding: process of converting an XML document into a set of tuples to be inserted into one or more relations
* XML-enabled database systems support automated publishing and shredding (**主要方式**)
* Some systems offer native storage of XML data using the xml data type.  Special internal data structures and indices are used for efficiency



# Appendix

## SQL/XML



## SQL Ext



## Web Services

**UDDI**：确保唯一

## HTML

```html
<HTML>

<HEAD>
    <TITLE>HTML 示例之一 </TITLE>

<body <TBODY bgcolor="white" text="blue">
    <DIV align=center>
        <FONT style="FONT-SIZE: 32px"><B>数据库系统原理课程简介</B></FONT>
        <FONT color=#999999><BR></FONT>
    </DIV>
    </TBODY>
    <P>Database is a large collection of data related to enterprises </P>
    <FONT color=black>
        <P><BR>　　数据库应用系统设计是根据应用需求建立数据库，并开发应用软件系统，
            是信息系统开发和建设中的重要内容.</P>
    </FONT>
    <P><BR>
        按照规范设计的方法，考虑数据库及其应用系统开发全过程，
        将数据库设计分为以下六个阶段：
        <BR>　　· 需求分析<BR>　　
        · 概念结构设计<BR>　　· 逻辑结构设计<BR>　　· 物理结构设计<BR>　　
        · 数据库实施<BR>　　· 数据库运行和维护 </P>
    <P>
        <FONT color=green>
            <B>在学习《数据库系统设计》时，需要进行做MINISQL实验，</B>
            这个实验的目的是使读者对数据库管理系统的工作过程有一个
            全面地、细致的了解。</FONT>
    </P>
    <P>
        <FONT color=red>附件：MINISQL实验指导书.doc </FONT>
    </P>
    </FONT>
    <TD width=8></TD>
    </TR>
    </TBODY>
    </TABLE>
</BODY>

</HTML>
```

<HEAD><TITLE>HTML 示例之一 </TITLE><body<TBODY bgcolor="white" text="blue"><DIV align= center><FONT style="FONT-SIZE: 32px"><B>数据库系统原理课程简介</B></FONT><FONT color= #999999><BR></FONT></DIV></TBODY><P>Database is a large collection of data related to enterprises </P><FONT color= black><P><BR>数据库应用系统设计是根据应用需求建立数据库，并开发应用软件系统，是信息系统开发和建设中的重要内容.</P></FONT><P><BR>按照规范设计的方法，考虑数据库及其应用系统开发全过程，将数据库设计分为以下六个阶段：<BR>· 需求分析<BR>· 概念结构设计<BR>· 逻辑结构设计<BR>· 物理结构设计<BR>· 数据库实施<BR>· 数据库运行和维护</P><P><FONT color= green><B>在学习《数据库系统设计》时，需要进行做MINISQL实验，</B>这个实验的目的是使读者对数据库管理系统的工作过程有一个全面地、细致的了解。</FONT></P><P><FONT color= red>附件：MINISQL实验指导书.doc </FONT></P></FONT><TD width= 8></TD></TR></TBODY></TABLE></BODY>

## JSON