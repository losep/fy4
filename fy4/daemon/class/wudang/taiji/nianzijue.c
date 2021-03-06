#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
    string msg;
    int extra; 
    if(me->query("class")!="wudang" && userp(me))
                return notify_fail("太极粘字诀是武当镇殿之宝。\n"); 
    extra = me->query_skill("taiji",1);
    if (extra < 60)
        return notify_fail("你的太极拳还不够高深！\n"); 
    if (userp(me) && me->query_skill_mapped("force") != "taijiforce")
                return notify_fail("［太极拳］需要［太极心法］的配合！\n"); 
    if( !target ) target = offensive_target(me);
    if( !target
        ||!target->is_character()
        ||!me->is_fighting(target) )
        return notify_fail("［粘字诀］只能对战斗中的对手使用。\n"); 
        if (target->query("step_less")==1) 
                return notify_fail(HIW"此人身势灵活，功力深湛，不会被此拳法迷惑的。\n"NOR); 
    if( target->is_busy() )
        return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n"); 
    if (extra < 165) {
        msg = CYN "$N使出太极拳法中的「粘」字诀，企图减缓$n的攻势，";
        me->start_busy(1);
        if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2
 ) {
            msg += "结果$p被$P攻了个措手不及！\n" NOR;
            target->start_busy( (int)me->query_skill("taiji",1) / 50 + random(2)
);
        }
        else {
            msg += "可是$p看破了$P的企图，并没有上当。\n" NOR;
        }
        message_vision(msg, me, target);
        return 1;
    }
    else {
        msg = HIR "$N真气鼓动，双拳幻化为无数大大小小的圆圈向$n攻去，";
        if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/3
 ) {
            msg += "结果$p头晕目眩，被$P的拳势围住不能脱身，频频中招！\n" NOR;
            target->start_busy(3);
            me->start_busy(random(2));
            target->receive_damage("kee",((int) me->query("max_force")/2),me);
            message_vision(msg, me, target);
            target->set_temp("damaged_during_attack", 1);
            COMBAT_D->report_status(target, 0);
            COMBAT_D->win_lose_check(me,target,1);
        }
        else {
            msg += "可是$p从容应招，将$P的攻势消于无形。\n" NOR;
            me->start_busy(random(2));
            message_vision(msg, me, target);
        } 
        return 1;
    }
}   
