#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
    string msg;
    int extra;
    object weapon;
    if( !target ) target = offensive_target(me); 
    if( !target
        ||!target->is_character()
        ||!me->is_fighting(target) )
        return notify_fail("［天雷一击］只能对战斗中的对手使用。\n");
        
    weapon = me->query_temp("weapon");
    extra = me->query_skill("thunderwhip",1);
    if( extra <=50) return notify_fail("你的天雷破还不够熟练！\n"); 
    if(!me->query("marks/hammerwhip") || me->query_skill("hammer")< 350
        || me->query_skill_mapped("hammer") != "pangu-hammer")
    {
                me->add_temp("apply/attack", extra);
                me->add_temp("apply/damage", extra);
                msg = HIR
                "$N"+HIR"力灌鞭梢，手中的"+weapon->query("name")+
                HIR"＂叭＂的一声，象条毒龙般向$n"NOR+HIR"钻去！" NOR;
                COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
                me->add_temp("apply/attack", -extra);
                me->add_temp("apply/damage", -extra);
                if (me->query_busy()<2) me->start_busy(2);
    }   else    {
                extra = me->query_skill("whip")+ me->query_skill("hammer");
                extra = extra /4;
                if (me->query("class")!="yinshi") extra = extra /2;
                me->add_temp("apply/attack", extra);
                me->add_temp("apply/damage", extra);
                msg = HIR
                "$N"+HIR"力灌鞭梢，手中的"+weapon->query("name")+
                HIR"＂叭＂的一声，象条毒龙般向$n"NOR+HIR"钻去！" NOR;
                COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
                me->add_temp("apply/damage", extra);    
           msg = HIR"$N"+HIR"急运真气，大喝一声，手中的"+weapon->query("name")+
                        HIR"夹着惊雷之势向$n"NOR+HIR"反卷而去！" NOR;
                COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
                me->add_temp("apply/attack", -extra);
                me->add_temp("apply/damage", -extra-extra);
                if (me->query_busy()<2) me->start_busy(2);
                }
        return 1;
}
