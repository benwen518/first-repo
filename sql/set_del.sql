1．在实验一创建的student,course,teacher,sc,tc表中用SQL语句完成以下操作：
（1）学生“刘家顺”要退学，请删除该学生的所有记录（包括选课记录和学生记录）。
delete from sc where 
sno=
(select sno
from student 
where sname='刘家顺');
commit;
delete from s where sname ='刘家顺';
commit;
（2）田小亮同学要转专业，他的学号为103465，将该同学的专业由原来的“软件工程”改为“计算机科学与技术”，班级由原来的“软工3班”修改为“计算机1班”。
修个多个元组的值
update student
set college='计算机科学与技术',
class = '计算机1班'
where sno =103465;
commit; 
（3）删除选修了“嵌入式系统与应用”但没有及格的选课记录。
delete from sc
where cno in(select cno from course where cname ='嵌入式系统与应用')
and grade<60;
commit;
（4）将元组（1203076，吕振华，男，1985/11/8，讲师，体育部）插入教师关系。
insert into t
values('1203076'，'吕振华'，'男'，to_date('1985/11/8','yyyy/mm/dd')，'讲师'，'体育部');
commit;
（5）在course表中插入以下两门课程信息： 
课程号：3094217，课程名：图与网络，课程学分：2，课程性质：选修，课程学时：32，开课学期：6
课程号：3094215，课程名：智能搜索与推荐技术，课程学分：2，课程性质：选修，课程学时：32，开课学期：7
insert into course(course_id, course_name, course_credit, course_type, course_hours, course_semester)
values  (课程号：3094217，课程名：图与网络，课程学分：2，课程性质：选修，课程学时：32，开课学期：6),
        (课程号：3094215，课程名：智能搜索与推荐技术，课程学分：2，课程性质：选修，课程学时：32，开课学期：7);
commit;
（6）创建名为xg_view的视图，在视图中显示所有信息工程学院教师的授课信息，包括教师姓名，职称，所授课程名称，授课班级，授课学期。
create xg_view
select t.tname,t.title,tc.id,tc.sclass,tc.semester
from t,tc
where t.tno=tc.tno and t.college ='信息工程学院';

（7）创建每个学生已修课程总学分的视图，视图名为xf_view，要求在视图中显示学生学号、姓名和总学分。
create xf_view

（8）在创建的视图中查询大数据2班每位学生已修的总学分。
（9）在系统表user_updatable_columns中查看视图xf_view是否可以更新，如果不能请说明原因。
2．在实验一创建的s，p，j和spj表中用SQL语句完成以下操作：
（1）现有一供应商，代码为s9、姓名为英特尔、所在城市西安，供应情况如下：供应零件p5给工程j7数量为600，供应零件p4给工程j4数量为500，请将此供应商的信息和供应信息插入数据库。
（2）请将北京供应商的供应数量加150。
（3）把全部红色零件的颜色改为黑色。
（4）由s5供给j4的零件p6改为由s1供应。
（5）请将（s2,j7,p4,510）插入供应情况关系。
（6）零件p1已经停产，请将p1的相关信息从数据库中删除。
（7）创建零件名为螺丝刀的供应情况的视图sd_view，视图中显示供应商名（Sname），零件名（Pname），零件重量（Weight），工程项目代码（Jno），供应数量（QTY）。
（8）在视图sd_view中查询供应数量在400到600之间的供应商姓名。
（9）请为三建工程项目建立一个供应情况的视图SJ_View，包括供应商编号，零件编号，供应数量。