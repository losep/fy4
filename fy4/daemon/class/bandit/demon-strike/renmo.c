 // tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra;
        if( !target ) target = offensive_target(me); 
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("����ħʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        extra = me->query_skill("demon-strike",1) ;
        if(extra < 60 ) return notify_fail("��ģ������ħ�������ƣݲ���������\n");
        msg = HIR "\n$N˫�۱�����һ�У���ħʽ�ݣ�˫��£��$n��" NOR;
        if(random((int)me->query("combat_exp")) >= (int)target->query("combat_exp"))
        {
        message_vision(msg+"\n",me,target);
        message_vision( HIB "$N����������ȫ��������Ӱ��ס�� һ��������$N������ӿ������\n" NOR,target);
        target->receive_wound("sen",extra);
        me->receive_heal("sen",extra);
        }       
        else{
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        }
        me->start_busy(2);
        return 1;
}