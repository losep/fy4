 // drift_sense.c
#include <ansi.h> 
inherit SSERVER; 
int conjure(object me, object target)
{
        object room;
        int marktime;
        if( me->is_fighting() )
                return notify_fail("ս�����޷�ʹ���ɷ���\n");
        if( me->query("atman") < 50 )
                return notify_fail("�������������\n");
        if( me->query("gin") <= 100 )
                return notify_fail("��ľ�������\n");
        if( me->is_ghost())
                return notify_fail("�����޷�ʹ���ɷ���\n");     
        if((int) me->query_skill("incarnation",1) < 160)
                return notify_fail("����������������\n");
        if (domain_file(file_name(environment(me)))=="eren2")
                return notify_fail("�˵ز���ʹ��ʱ��ת����\n");
        if(environment(me)->query("no_fly")||environment(me)->query("no_death_penalty")
                || environment(me)->query("no_fly"))
                return notify_fail("�˵ز���ʹ��ʱ��ת����\n"); 
        me->add("atman", -50);
        me->receive_damage("gin", 100);
        me->start_busy(1);
        message_vision( HIY "$N�����ķ���˫��һ�ӣ�����һ����ɫ�����������ʧ�� ....\n" NOR, me);
        room = environment(me);
        marktime=900+random((me->query_skill("incarnation",1)-80)*100);
        me->set_temp("timespacemark",base_name(room));
    me->set_temp("timespacemark_time",time()+marktime);
        return 1;
}     