 // tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra, bonus;
        int exp_bonus; 
//      if(me->query("class")!="yinshi")
//              return notify_fail("蓝大先生只把［乱泼风］传给帝王谷弟子。\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("［乱泼风］只能对战斗中的对手使用。\n");
        extra = me->query_skill("unarmed")/2;
        bonus = me->query_skill("pofeng-strike",1);
        
        exp_bonus=(me->query("combat_exp")-3000000)/1000*extra/6000;
        if (exp_bonus<0) exp_bonus=0;   
        if (exp_bonus>100) exp_bonus=100;
        
        me->add_temp("apply/attack", extra + exp_bonus);        
        me->add_temp("apply/damage", extra + bonus);
        msg = HIR  "$N双掌血红，五指绽开，无数道掌风破空而出，隐隐带着雷声迅疾无比地击向$n！" NOR;
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        me->add_temp("apply/attack", -extra - exp_bonus);
        me->add_temp("apply/damage", -extra - bonus);
        if (me->query_busy()<2) me->start_busy(2);
        return 1;
}
