#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,n;
        object weapon;
        extra = me->query_skill("xuanyuan-axe",1);
        if ( extra < 40) return notify_fail("你的轩辕斧法还不够纯熟！\n");
        
        if (userp(me) && me->query_skill_mapped("force") != "longlife-force")
                return notify_fail("轩辕斧法需要苍生诀的配合！\n");
                
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("［鬼斧神工］只能对战斗中的对手使用。\n");
        if (extra>130 && me->query("class")=="knight") n=0;
                else if (extra>80) n=1;
                else n=2; 
        weapon = me->query_temp("weapon");
        me->add_temp("apply/attack",extra);
        msg = HIY  "$N气沉丹田，怒吼声中手中的"+ weapon->name()+HIY"雷霆霹雳般向$n"+HIY"砍出一斧［鬼斧］！" NOR;
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        msg = HIY  "$N筋骨格格直响，双臂骤然变粗，手中的"+ weapon->name()+HIY"回飞，旋风般的又是一斧［神工］！" NOR;
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        me->add_temp("apply/attack",-extra);
        if (me->query_busy()<2+n) 
                me->start_busy(2+n);
        return 1;
}
