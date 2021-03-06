 // tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int myexp,yourexp,lvl,n;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「降龙无悔」只能对战斗中的对手使用。\n");
        myexp = (int) me->query("combat_exp");
        yourexp = (int) target->query("combat_exp");
        lvl = (int) me->query_skill("dragonstrike",1);
        msg = HIR "$N将「降龙十八掌」的十八式融会贯通，幻出十八个掌影一连击向$n"HIR"的十八处要害！" NOR;
        if(yourexp < random(myexp*(2+lvl/20)))  {
                if( random(2)&& !target->is_busy())     {
                        message_vision(msg + "\n", me, target);
                        msg = "结果$n被$N攻了个手忙脚乱！\n";
                        message_vision(msg, me, target);
                        target->start_busy(3);
                } else  {
                        me->add_temp("apply/attack",lvl);
                        me->add_temp("apply/damage",lvl);
                        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
                        me->add_temp("apply/attack",-lvl);
                        me->add_temp("apply/damage",-lvl);  
                }
        } else  {
                me->add_temp("apply/attack",lvl/2);
                me->add_temp("apply/damage",lvl);
                COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
                me->add_temp("apply/attack",-lvl/2);
                me->add_temp("apply/damage",-lvl);
        }
        if ((int) me->query_skill("dragonstrike",1)>155 && me->query("class")=="beggar") 
                {       
                        me->add_temp("apply/attack",lvl);
                   me->add_temp("apply/damage",lvl*2);
                        msg=HIR "$N大喝一声，使出「降龙十八掌」最后一招 "+HIG"飞龙在天"NOR+HIR" 击向$n"HIR"的$l。"NOR;
                        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);  
                        me->add_temp("apply/attack", -lvl);
                        me->add_temp("apply/damage",-lvl*2);    
                }
        if (me->query_busy()<2) 
                me->start_busy(2);
        return 1;
}
