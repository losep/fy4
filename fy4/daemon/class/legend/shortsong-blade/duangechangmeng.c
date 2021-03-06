 // tie@fengyun
//食芝英，饮醴泉，柱杖桂枝佩秋兰。
//绝人事，游浑元，若疾风游［炎欠］翩翩。
//景未移，行数千，寿如南山不忘愆。
/*
    短歌行（二首） 
对酒当歌，人生几何？
譬如朝露，去日苦多。
慨当以慷，忧思难忘。
何以解忧？唯有杜康。
青青子衿，悠悠我心。
但为君故，沈吟至今。
呦呦鹿鸣，食野之苹。
我有嘉宾，鼓瑟吹笙。
明明如月，何时可掇？
忧从中来，不可断绝。
越陌度阡，枉用相存。
契阔谈宴，心念旧恩。
月明星稀，乌鹊南飞，
绕树三匝，何枝可依？
山不厌高，海不厌深。
周公吐哺，天下归心。 
*/
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int third_blade(object me,object target,int extra,object weapon);
int perform(object me, object target)
{
        string msg;
        int extra,i;
        object weapon;
        extra = me->query_skill("shortsong-blade",1);
        if ( extra < 30) return notify_fail("你的短歌刀法还不够纯熟！\n");
        
        if (userp(me) && me->query_skill_mapped("force") != "qidaoforce")
                return notify_fail("［短歌长梦］需要［棋道心法］的配和！\n"); 
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
   ||      !me->is_fighting(target) )
                return notify_fail("［短歌长梦］只能对战斗中的对手使用。\n");
        weapon = me->query_temp("weapon"); 
if (me->query("class")!="legend") {
        msg = HIY  "$N使出短歌刀法中的［短歌长梦］，一招连环两式，手中的"+ weapon->name()+  HIY"闪电般向$n"HIY"攻出第一刀！”" NOR;
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
//      COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);
        msg = HIY  "第二刀！" NOR;
        me->add_temp("apply/damage",extra);
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        me->add_temp("apply/damage",-extra);
        if (extra<150) {
        if (me->query_busy()<3) me->start_busy(3);
        return 1;
        } 
        me->add_temp("apply/damage",extra*2);
        msg = HIY  "$N更不放松，竟又挥出第三刀！" NOR;
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        me->add_temp("apply/damage",-extra*2);
        if (me->query_busy()<3) me->start_busy(3);
        return 1;
} 
        me->add_temp("apply/damage",extra);
        msg = HIY  "$N使出短歌刀法中的［短歌长梦］，一招连环两式，\n手中的"+ weapon->name()+ HIY "闪电般向$n"HIY"攻出第一刀！“食芝英，饮醴泉，柱杖桂枝佩秋兰。”" NOR;
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        msg = HIY  "第二刀！“绝人事，游浑元，若疾风游赕翩翩。”" NOR;
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        me->add_temp("apply/damage",-extra);            
        
        if (extra <150) {
        if (me->query_busy()<3) me->start_busy(3);
        return 1;
        }
        
//              if(i=random(2))
//                      call_out("third_blade",i,me,target,extra,weapon);
//              else
        third_blade(me,target,extra,weapon);                            
        if (me->query_busy()<3) me->start_busy(3);
        return 1;
   
}
        
int third_blade(object me,object target,int extra,object weapon)
{
        string msg;
        int bonus, exp_bonus;
        
        if(!me||!target||!me->is_fighting(target)||environment(target)!=environment(me)) return 0;
        if(!present(weapon,me)||weapon->query("equipped")!="wielded")
                return 0;
        exp_bonus = me->query("combat_exp")/1000*extra/8000;            
        me->add_temp("apply/damage",extra*6+exp_bonus);
        msg = HIY  "$N更不放松，竟又挥出第三刀！“景未移，行数千，寿如南山不忘愆。”" NOR;
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        me->add_temp("apply/damage",-extra*6-exp_bonus);
        return 1;
} 
