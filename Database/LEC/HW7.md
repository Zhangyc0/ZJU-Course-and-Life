# HW7

#### 6.1

#### ![image-20220421192452710](C:\Users\MSI-NB\AppData\Roaming\Typora\typora-user-images\image-20220421192452710.png)6.2

###### a.

![image-20220421193123291](C:\Users\MSI-NB\AppData\Roaming\Typora\typora-user-images\image-20220421193123291.png)

###### b.

![image-20220421193146465](C:\Users\MSI-NB\AppData\Roaming\Typora\typora-user-images\image-20220421193146465.png)

#### 6.21

###### a.

![image-20220421205109080](C:\Users\MSI-NB\AppData\Roaming\Typora\typora-user-images\image-20220421205109080.png)

###### b.

![image-20220421205510472](C:\Users\MSI-NB\AppData\Roaming\Typora\typora-user-images\image-20220421205510472.png)

#### 6.22

Figure：

![image-20220421210616499](C:\Users\MSI-NB\AppData\Roaming\Typora\typora-user-images\image-20220421210616499.png)

Code：

```sql
brand(name)
model(model id,name)
vehicle(VIN)
option(option id,specification)
customer(customer id,name,address)
dealer(dealer id,name,address)
has models(name,model id ,foreign key name references brand ,foreign key model id references model)
has vehicles(model id,VIN,
foreign key VIN references vehicle,
foreign key model id references model
)
available options(model id,
option id,
foreign key option id references option,
foreign key model id references model
)
has options(VIN,model id,
option id,
foreign key VIN references vehicle,
foreign key (model id, option id) references available options
)
has dealer(VIN,dealer id ,
foreign key dealer id references dealer,
foreign key VIN references vehicle
)
owned by(VIN,customer id,
foreign key customer id references customer,
foreign key VIN references vehicle
)

```



