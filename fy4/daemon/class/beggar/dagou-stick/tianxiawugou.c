 // mimicat@fy4
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,i, bonus, exp_bonus;
        
        object weapon, *enemy;
        
/*      
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("［天下无狗］只能对战斗中的对手使用。\n");
*/
        if((int)me->query_skill("dagou-stick",1) < 120 && userp(me))
                return notify_fail("你的打狗棒法还不够熟练！\n");        
        enemy=me->query_enemy();
        if(!sizeof(enemy))
                return notify_fail("［天下无狗］只能对战斗中的对手使用。\n");
        if(target)
                return notify_fail("这个绝招不需要指定使用对象！！\n");
                
        weapon = me->query_temp("weapon"); 
        extra = me->query_skill("dagou-stick");
        bonus = 0;
        if (extra>150 && me->query("class")== "beggar") bonus= extra; 
        me->add_temp("apply/attack", extra/2);  
        me->add_temp("apply/damage", extra+bonus);
        msg = HIR  "$N低喝一声［天下无狗］，内力聚于手中的"NOR+ weapon->name() +"，"+
weapon->name() +
HIR"化成满天棍影，\n昏天黑地般盖向在场每一个人！\n" NOR;
        message_vision(msg,me);
        for(i=0;i<sizeof(enemy);i++)
        {
                msg=HIY"$N手中的$w直取$n的$l！！"NOR;
                me->set_temp("dagou/pfm",1);
           COMBAT_D->do_attack(me,enemy[i], TYPE_PERFORM,msg);
                me->delete_temp("dagou/pfm",1);
        }
        me->add_temp("apply/attack", -extra/2);
        me->add_temp("apply/damage", -extra-bonus);
        if (me->query_busy()<2) 
                me->start_busy(2);
        return 1;
}  
