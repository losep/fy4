#include <ansi.h>
inherit SKILL; 
void setup() {
        set("name",                             "������");
        set("type",                             "knowledge");
        set("learn_bonus",                      -100);
        set("practice_bonus",           -100);
        set("black_white_ness",         -100);
        set("effective_level",          100); 
} 
int valid_learn(object me)
{
        if( (int)me->query_skill("animal-training",1) < (int)me->query_skill("summonwolf",1)) {
                return notify_fail("���ѵ����������ͨ���޷�������Ӹ���Ļ�������\n");
        }
        return 1;
} 
void skill_improved(object me)
{
    int s;
    s = me->query_skill("summonwolf", 1);
    if (s== 150 && me->query("class")=="wolfmount") {
       tell_object(me,HIW "��Ի���֮�����˽�����һ����Ծ��\n"NOR);
       tell_object(me,HIW "�㻽�ǵĸ��������ˣ�\n"NOR);
       } 
    if (s== 180 && me->query("class")=="wolfmount") {
       tell_object(me,HIW "��Ի���֮�����˽�����һ����Ծ��\n"NOR);
       tell_object(me,HIW "����������ڻ����ˣ�\n"NOR);
       }
} 