--create database library;
--use library;
--create table book (bno char(8) ,
--			category char(10),
--			title varchar(40),
--			press varchar(30),
--			year int,
--			author varchar(20),
--			price decimal(7,2),
--			total int ,
--			stock int,
--			primary key(bno));

--create table card(
--		cno char(7),
--		name varchar(10),
--		department  varchar(40),
--		type char(1),
--		primary key(cno),
--		check(type in ('T', 'G', 'U', 'O'))
--		) 

--create table borrow(
--	cno char(7),
--	bno char(8),
--	borrow_date datetime,
--	return_date datetime,
--	foreign key (bno)
--		references book(bno)
--		on delete cascade,
--	foreign key (cno)
--		references card(cno)
--		on update cascade
--) 

--drop table borrow;
--insert into book 
--values('10', '����ѧ','�µ�����','�㽭��ѧ',2002,'������',48.00,20,4);
--insert into card
--values('zju1001','�׷�','�����','T');
insert into borrow
values ('zju1001','9','2011-09-10','2012-2-23');

--insert into book
--values('10', '����ѧ','������Դ','�����ѧ',2002,'Darwin',48.00,20,4);

--insert into card
--values ('zju1002','���','����ѧ','K');
select num=count(*) from borrow where cno=c;
SET num = select count(*) from borrow where cno=c;
--update book
--set bno = '100'
--where title = '�µ�����';
delimiter $
create trigger before_borrow_insert
before insert on borrow for each row
begin
declare num int;
declare c char(10);
Set c = select cno from inserted;
SET num = select count(*) from borrow where cno=c;
if (num = 2) then signal sqlstate '45000'
set message_text = 'һλͬѧһ��ѧ�ڲ����Խ������飡';
end if;
end$
delimiter ;


delimiter $
create trigger before_borrow_insert
before insert on borrow for each row
begin
declare num int;
declare c char(10);
select cno from inserted into c;
select count(*) from borrow where cno=c into num;
if (num = 2) then signal sqlstate '45000'
set message_text = 'һλͬѧһ��ѧ�ڲ����Խ������飡';
end if;
end$
delimiter ;