 // combatd.c
// Copyright (C) 1995 - 2002, by FengYun Workshop. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
//
// Last modification:
//              - 07/02/2001 by Daniel Q. Yu.
//                      * Put in counter_attack etc.
//              - 07/14/2001 by Daniel Q. Yu.
//                      * Fix some counter_attack message problems.
//              - 07/17/2001 by Daniel Q. Yu.
//                      * Add counter_attack messages.
//              - 07/20/2001 by Daniel Q. Yu.
//                      * Change death penalty.
//              - 04/17/2002 by Neon
//                      * Change report_status
//              - 04/26/2002 by silencer
//                      * added magic/spells check in winner/loser
//                      * added function win_lose_check()
//                      * added alternate death penalty for certain areas.
//              - 07/22/2002 by silencer
//                      * fixed damage report in weapon damage, it reported only random(damage).
//              - 10/12/2002 by love
//                      * add items' hit_ob,parry_ob,dodge_ob 
//#pragma optimize
#define LOWER_LIMIT 2000
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h> 
int give_reward(object who,mapping quest);
mapping get_action(object me, int attack_type); 
string *guard_msg = ({
        CYN "$N注视著$n"NOR+CYN"的行动，企图寻找机会一击成功。\n" NOR,
        CYN "$N正盯著$n"NOR+CYN"的一举一动，随时准备发动攻势。\n" NOR,
        CYN "$N以守为攻，想要找出$n"NOR+CYN"的破绽。\n" NOR,
        CYN "$N缓缓地移动着脚步，等待着最佳的出招方位。\n" NOR,
        CYN "$N眼睛眨也不眨地盯着$n"NOR+CYN"，伺机出手。\n" NOR,
}); 
string *catch_hunt_msg = ({
   HIW "$N和$n"NOR+HIW"仇人相见分外眼红，立刻打了起来！\n" NOR,
        HIW "$N对著$n"NOR+HIW"大喝：「可恶，又是你！」\n" NOR,
        HIW "$N和$n"NOR+HIW"一碰面，二话不说就打了起来！\n" NOR,
        HIW "$N一眼瞥见$n"NOR+HIW"，大叫一声冲了过来！\n" NOR,
        HIW "$N一见到$n"NOR+HIW"，愣了一愣，大叫：「我宰了你！」\n" NOR,
        HIW "$N喝道：「$n"NOR+HIW"，我们的帐还没算完，看招！」\n" NOR,
        HIW "$N喝道：「$n"NOR+HIW"，看招！」\n" NOR,
}); 
string *winner_msg = ({
        CYN "\n$N哈哈大笑，说道：承让了！\n\n" NOR,
        CYN "\n$N双手一拱，笑著说道：承让！\n\n" NOR,
        CYN "\n$N胜了这招，向後跃开三尺，笑道：承让！\n\n" NOR,
        CYN "\n$n脸色微变，说道：佩服，佩服！\n\n" NOR,
        CYN "\n$n向後退了几步，说道：这场比试算我输了，佩服，佩服！\n\n" NOR,
        CYN "\n$n向後一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n" NOR,
}); 
string *counter_msg = ({
        HIR "$N"HIR"全然不顾$n"NOR+HIR"的攻击，以快制快。\n" NOR,
        HIR "$N"HIR"不求自保，奋力抢攻而上。\n" NOR,
}); 
object protector;
int attacker_damage = 0;
int victim_damage = 0;
int protector_damage = 0;
string parry_message = "";
string dodge_message = "";
string protect_message = "";
string counter_message = "";
string damage_message = "";
string inflict_message = "";
string result_message = ""; 
void create() {
        seteuid(ROOT_UID);
} 
string damage_msg(int damage, string type) {
        string str; 
        if(damage <= 0) {
                return "结果没有造成任何伤害。\n";
        }
//  write(" damage is "+(string)(damage)+". \n"); 
        switch( type ) {
                case "拉伤":
                case "割伤":
                        if( damage < 100 ) return "结果只是轻轻地划破$n的皮肉。\n";
                        else if( damage < 200 ) return "结果在$n的$l划出一道细长的血痕。\n";
                        else if( damage < 400 ) return "结果「嗤」地一声划出一道伤口！\n";
                        else if( damage < 800 ) return "结果「嗤」地一声划出一道血淋淋的伤口！\n";
                        else if( damage < 1600 ) return "结果「嗤」地一声划出一道又长又深的伤口，溅得$N满脸鲜血！\n";
                        else return "结果只听见$n一声惨嚎，$w已在$n$l划出一道深及见骨的可怕伤口！！\n";
                        break;
                case "刺伤":
                        if( damage < 100 ) return "结果只是轻轻地刺破$n的皮肉。\n";
                        else if( damage < 200 ) return "结果在$n$l刺出一个创口。\n";
                        else if( damage < 400 ) return "结果「噗」地一声刺入了$n$l寸许！\n";
                        else if( damage < 800 ) return "结果「噗」地一声刺进$n的$l，使$p不由自主地退了几步！\n";
                        else if( damage < 1600 ) return "结果「噗嗤」地一声，$w已在$n$l刺出一个血肉模糊的血窟窿！\n";
                        else return "结果只听见$n一声惨嚎，$w已在$n的$l对穿而出，鲜血溅得满地！！\n";
                        break;
                case "瘀伤":
                        if( damage < 50 ) return  "结果只是轻轻地碰到，比拍苍蝇稍微重了点。\n";
                        else if( damage < 100 ) return "结果在$n的$l造成一处瘀青。\n";
                        else if( damage < 200 ) return "结果一击命中，$n的$l登时肿了一块老高！\n";
                        else if( damage < 400 ) return "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n";
                        else if( damage < 800 ) return "结果「砰」地一声，$n退了两步！\n";
                        else if( damage < 1200 ) return "结果这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n";
                        else if( damage < 1600 ) return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n";
                        else return "结果只听见「砰」地一声巨响，$n像一捆稻草般飞了出去！！\n";
                        break;
                case "抓伤":
                        if( damage < 50 ) return "结果只是轻轻地抓到，比抓痒稍微重了点。\n";
                        else if( damage < 100 ) return "结果在$n的$l抓出几条血痕。\n";
                        else if( damage < 200 ) return "结果一抓命中，$n的$l被抓得鲜血飞溅！\n";
                        else if( damage < 400 ) return "结果「嗤」地一声，$l被抓得深可见骨！！\n";
                        else if( damage < 800 ) return "结果一抓命中，$n的$l被抓得血肉横飞！！！\n";
                        else if( damage < 1200 ) return "结果这一下「嗤」地一声抓得$n连晃好几下，差一点摔倒！\n";
                        else if( damage < 1600 ) return "结果$n哀号一声，$l被抓得筋断骨折！！\n";
                        else return "结果只听见$n一声惨嚎，$l被抓出五个血窟窿！鲜血溅得满地！！\n";
                        break;
           case "反弹伤":
                        if( damage < 10 ) return "$N受到$n$z的反震，闷哼一声。\n";
                        else if( damage < 20 ) return  "$N被$n的$z震得气血翻腾，大惊失色。\n";
                        else if( damage < 40 ) return "$N被$n的$z震得站立不稳，摇摇晃晃。\n";
                        else if( damage < 80 ) return "$N被$n以$z反震，「嘿」地一声退了两步。\n";
                        else if( damage < 160 ) return "$N被$n的$z反弹回来的力量震得半身发麻。\n";
                        else if( damage < 240 ) return "$N被$n的$z反弹力一震，胸口有如受到一记重击，连退了五六步！\n";
                        else if( damage < 320 ) return "$N被$n的$z一震，眼前一黑，身子向後飞出丈许！！\n";
                        else return "$N被$n的$z一震，眼前一黑，狂吐鲜血，身子象断了线的风筝向後飞去！！\n";
                        break;
                default:
                        if(!type) type = "伤害";
                        if(damage < 50) str =  "结果只是勉强造成一处轻微";
                        else if( damage < 100 ) str = "结果造成轻微的";
                        else if( damage < 200 ) str = "结果造成一处";
                        else if( damage < 400 ) str = "结果造成一处严重";
                        else if( damage < 600 ) str = "结果造成颇为严重的";
                        else if( damage < 800 ) str = "结果造成相当严重的";
                        else if( damage < 1200 ) str = "结果造成十分严重的";
                        else if( damage < 1600 ) str = "结果造成极其严重的";
                        else str =  "结果造成非常可怕的严重";
                        return str + type + "！\n";
                }
} 
//dam_type, kee:1 sen:2 gin:3, default =1
string eff_status_msg(int ratio, int dam_type) {
        if( ratio==100 ) return HIG "看来身上并无丝毫伤痕。" NOR;
        if( ratio > 95 ) return HIG "似乎只受了点轻伤，但无伤大体。" NOR;
        if( ratio > 90 ) {
                if (dam_type == 3)
                        return HIY "看来有些萎靡，好像精力受损。" NOR;
                else if (dam_type == 2)
                        return HIY "精神似乎受了些损伤，表情有点僵硬。" NOR;
                else    return HIY "可能受了几处皮肉伤。" NOR;
        }
        if( ratio > 80 ) return HIY "受了几处创伤，似乎并不碍事。" NOR;
        if( ratio > 60 ) {
                if (dam_type == 3)
                        return HIY "骨软筋麻，涕泪交流。" NOR;
           else if (dam_type == 2)
                        return HIY "神情惨然，耳鼻中竟然有鲜血渗出。" NOR;
                else    return HIY "身上受伤不轻，正在流着血。" NOR;
        }
        if( ratio > 40 ) {
                if (dam_type == 3)
                        return HIY "面部抽搐不止，已经不能自己。" NOR;
                else    return HIR "流血不止，动作散乱，已经在走下坡路了。" NOR;
        }
        if( ratio > 30 ) return HIR "伤痕累累，正在勉力支撑著不倒下去。" NOR;
        if( ratio > 20 ) return HIR "遍体鳞伤，只剩下最后一口气了。" NOR;
        if( ratio > 10 ) return RED "浑身浴血，就要倒在地上。" NOR;
        if( ratio > 5  ) return RED "瞳空放大，已经奄奄一息，命在旦夕了。" NOR;
        return RED "如风中残烛，随时都可能断气。" NOR;
} 
//dam_type, kee:1 sen:2 gin:3, default =1
string status_msg(int ratio, int dam_type) {
        if( ratio==100 ) return HIG "精力充沛，神完气足，" NOR;
        if( ratio > 95 ) return HIG "似乎有些疲惫，但是仍然十分有活力，" NOR;
        if( ratio > 90 ) return HIY "看起来可能有些不济，" NOR;
        if( ratio > 80 ) {
                if (dam_type == 3)
                        return HIY "精力有点不足，但仍攻守从容，" NOR;
                else if (dam_type == 2)
                        return HIY "神情有些恍惚，但仍应付自如，" NOR;
                else    return HIY "动作有点不太灵光，但仍有条不紊，" NOR;
        }
        if( ratio > 60 ) {
                if (dam_type == 3)
                        return HIY "行动虽然无碍，精力明显跟不上了，" NOR;
                else if (dam_type == 2)
                        return HIY "反应开始迟缓，双目无神，" NOR;
                else    return HIY "气喘嘘嘘，脸色惨白，" NOR;
        }
        if( ratio > 40 ) {
                if (dam_type == 3)
                        return HIR "精力涣散，似乎对痛痒都失去知觉，" NOR;
                else if (dam_type == 2)
                        return HIR "眼光迷离，六神无主，" NOR;
           else    return HIR "似乎十分疲惫，看来需要好好休息了，" NOR;
        }
        if( ratio > 30 ) return HIR "头重脚轻，正在勉力支撑著不倒下去，" NOR;
        if( ratio > 20 ) {
                if (dam_type == 3)
                        return HIR "看来已经麻木不仁了，" NOR;
                else if (dam_type == 2)
                        return HIR "看起来已经魂不守舍了，" NOR;
                else    return HIR "看起来已经力不从心了，" NOR;
        }
        if( ratio > 10 ) return RED "摇头晃脑、歪歪斜斜，濒于晕倒，" NOR;
        return RED "已经陷入半昏迷状态，神智全失，" NOR;
} 
varargs void report_status(object ob, int i) {
        int eff_ratio = 100;
        int ratio = 100;
        int k_stat, g_stat, s_stat;
        int d_type = 1;
        int e_type = 1; 
        k_stat = (int) ob->query("kee") * 100 / (int)ob->query("max_kee");
        s_stat = (int) ob->query("sen") * 100 / (int)ob->query("max_sen");
        g_stat = (int) ob->query("gin") * 100 / (int)ob->query("max_gin"); 
        if (ratio > k_stat ) {
                ratio =  k_stat;
        }
        if (ratio > s_stat ) {
                ratio =  s_stat;
                d_type = 2;
        }
        if (ratio > g_stat ) {
                ratio =  g_stat;
                d_type = 3;
        } 
        k_stat = (int) ob->query("eff_kee") * 100 / (int)ob->query("max_kee");
        s_stat = (int) ob->query("eff_sen") * 100 / (int)ob->query("max_sen");
        g_stat = (int) ob->query("eff_gin") * 100 / (int)ob->query("max_gin"); 
        if (eff_ratio > k_stat ) {
                eff_ratio =  k_stat;
        }
   if (eff_ratio > s_stat ) {
                eff_ratio =  s_stat;
                e_type = 2;
        }
        if (eff_ratio > g_stat ) {
                eff_ratio =  g_stat;
                e_type = 3;
        } 
        message_vision("( $N" + status_msg(ratio, d_type) + eff_status_msg(eff_ratio, e_type) + " )\n", ob); 
}  
// This function calculates the combined skill/combat_exp power of a certain
// skill. This value is used for A/(A+B) probability use.
int skill_power(object ob, int usage) {
        int status, level, enc, max_enc, result;
        int bonus, exp;
        string skill;
        object weapon;
        string wptype,pski; 
        // Check for the total weight a player is carrying.
        // Skill power will descrease as you carry more things.
        // NPC does not have this restrication.
        if(!userp(ob)) {
                enc = 10;
        } else {
                max_enc = (int)ob->query_max_encumbrance();
                max_enc = max_enc > 0 ? max_enc : 1;
                enc = (max_enc  + max_enc/10 - 1 - (int) ob->query_encumbrance() ) * 10 / max_enc;
        } 
        level = 1;
        switch(usage) {
                case SKILL_USAGE_ATTACK:
                        skill = objectp(weapon = ob->query_temp("weapon")) ? weapon->query("skill_type") : "unarmed";
                        level = ob->query_skill(skill);
                        level += ob->query_temp("apply/attack");
                        level += ob->query_temp("apply/"+skill);//let's have apply/axe,apply/unarmed，这样的效果
                        bonus= ob->query_temp("bonus/attack");
                        break;
                case SKILL_USAGE_DODGE:
                        level = ob->query_skill("dodge");
                   level += ob->query_temp("apply/dodge");
                        level += ob->query_temp("apply/defense");
                        bonus= ob->query_temp("bonus/dodge");
                        break;
                case SKILL_USAGE_PARRY:
                        skill = objectp(weapon = ob->query_temp("weapon")) ? "parry" : "unarmed";
                        if(objectp(weapon))
                        {
                                wptype=weapon->query("skill_type");
                                if(stringp(pski=ob->query_skill_mapped(skill)))
                                if(SKILL_D(pski)->valid_enable(wptype))
                                        level = ob->query_skill(skill);
                                else
                                        level = ob->query_skill(skill,1)/2;
                        }
                        else    {
                                level=ob->query_skill("parry",1)/2;
                                if (ob->query_skill_mapped(skill))
                                        level += ob->query_skill(ob->query_skill_mapped(skill));
                        }
                        level += ob->query_temp("apply/parry");
                        level += ob->query_temp("apply/defense");
                        bonus= ob->query_temp("bonus/parry");
                        break;
                case SKILL_USAGE_MOVE:
                        level = ob->query_skill("move");
                        level += ob->query_temp("apply/move");
                        bonus= ob->query_temp("bonus/move");
                        break;
        }
        result = level/10*level/10*level/5;
        if(bonus>0)
                result+=bonus/10*bonus/10*bonus/5;
        if((status = ob->query("kee")) > 0 ) {
                if(status<ob->query("max_kee"))
                result = status*100/ob->query("max_kee")*result/100;
        } else {
                result = result /4000;
        }
   exp=(int)(ob->query("combat_exp")/25);
        if(ob->query("sen") > 0 && ob->query("gin") > 0) {
                status=3*ob->query("sen")+ob->query("gin");
                if(status<3*ob->query("max_sen")+ob->query("max_gin"))
                exp = status*100/(3*ob->query("max_sen")+ob->query("max_gin"))*exp/100;
        } else {
                exp = exp /4000;
        }
        result = result + exp;
        result = result * enc / 10;
        return result > 1 ? result : 1;
} 
// Reward the winner.
void fight_reward(object winner, object loser) {
        object owner; 
        if(owner=winner->query("possessed")) {
                winner = owner;
        }
        winner->win_enemy(loser);
} 
// Penalize the loser.
void fight_penalty(object winner, object loser) {
        object owner; 
        if(owner=loser->query("possessed")) {
                loser = owner;
        }
        loser->lose_enemy(winner);
} 
string prepare_final_message(object attacker, object victim,string w_name, string vw_name,mapping action, string result) {
        string output, *limbs, limb; 
        limbs = victim->query("limbs");
        limb = limbs[random(sizeof(limbs))];
        output = replace_string(result, "$l", limb );
        if(stringp(vw_name)) {
                output = replace_string(output, "$v", vw_name);
        }
        if(victim->query_skill_mapped("iron-cloth")) {
                output = replace_string(output, "$z",  SKILL_D(victim->query_skill_mapped("iron-cloth"))->name());
        }

        if(stringp(w_name)) {
                output = replace_string(output, "$w", w_name);
        } else if(stringp(action["weapon"])) {
                output = replace_string(output, "$w", action["weapon"] );
        }
        return output;
} 
// attack_damage
// Return the damage an attack can do
int attack_damage(object attacker, mapping action, object victim) {
        int damage, damage_bonus, force_factor, bounce, att_combat_exp;
        string force_skill, attack_skill, martial_skill;
        object attweapon;
        mixed tmp;
        function f; 
        damage_message = "";
        // Weapon damage
        attweapon = attacker->query_temp("weapon");
        damage = (attacker->query_temp("apply/damage"))+ 2;
        damage = (damage + random(damage)) / 2; 
        // Action damage
        if(action["damage"]) {
                damage += action["damage"] * damage / 1000;
        } 
        // Strength damage bonus.
        damage_bonus = attacker->query_str();
        damage_bonus = damage_bonus * damage_bonus / 10;
        // if use weapon, effectiveness only 3/4
        if(attweapon) {
                damage_bonus -= damage_bonus/4;
        } 
        // Let force skill take effect.
        force_factor = attacker->query("force_factor");
        if(force_factor && (force_skill = attacker->query_skill_mapped("force"))) {
                tmp = SKILL_D(force_skill)->hit_ob(attacker, victim, damage_bonus, force_factor);
                if(stringp(tmp) ) {
                        damage_message += tmp;
                } else if(intp(tmp)) {
                        damage_bonus += tmp;
           }
        } 
        // Action force damage
        if(action["force"]) {
                damage_bonus += action["force"] * damage_bonus / 1000;
        } 
        // Attack Skill damage
        if(objectp(attweapon)) {
                attack_skill = attweapon->query("skill_type");
        } else {
                attack_skill = "unarmed";
        } 
        if(martial_skill = attacker->query_skill_mapped(attack_skill) ) {
                tmp = SKILL_D(martial_skill)->hit_ob(attacker, victim, damage_bonus);
                if(stringp(tmp) ) {
                        damage_message += tmp;
                } else if(intp(tmp)) {
                        damage_bonus += tmp;
                }
        } 
        // Let weapon or monster have their special damage.
        if(objectp(attweapon)) {
                tmp = attweapon->hit_ob(attacker, victim, damage_bonus);
                if(stringp(tmp) ) {
                        damage_message += tmp;
                } else if(intp(tmp)) {
                        damage_bonus += tmp;
                }
                if(functionp(f=attweapon->query_temp("hit_ob",1)))
                {
                        tmp=evaluate(f,attacker, victim, damage_bonus);
                        if(stringp(tmp) )
                        {
                                damage_message += tmp;
                        }
                        else if(intp(tmp))
                        {
                                damage_bonus += tmp;
                        }
           } 
        } else {
                tmp = attacker->hit_ob(attacker, victim, damage_bonus);
                if(stringp(tmp) ) {
                        damage_message += tmp;
                } else if(intp(tmp)) {
                        damage_bonus += tmp;
                }
        } 
        // Add damage bonus.
        if(damage_bonus > 0) {
                damage += (damage_bonus + random(damage_bonus))/2;
        } 
        // Let combat exp take effect
        bounce = victim->query("combat_exp");
        att_combat_exp = attacker->query("combat_exp");
        while(random(bounce) > att_combat_exp && damage > 0) {
                damage -= damage / 5;
                bounce/= 2;
        } 
        // See how much damage our flexibility can absorb
        damage = damage - ((int)victim->query_fle())
                        - ((int)victim->query_temp("apply/extra_fle")); 
        if(damage < 0) damage = 0;
        return damage*3;
} 
// inflict_damage
// Inflict damange on the victim.
int inflict_damage(object attacker, object victim, int damage, mapping action) {
        int absorb_vic, bounce, wounded,s_ratio,s_force,eff_ness, total_damage;
        string absorb_skill,s_msg,s_type;
        mapping shield;
        object weapon; 
        inflict_message = "";
        weapon=attacker->query_temp("weapon");
        // how much absort_vic?
        if(random(100)>5)
        {
                if(victim->query_skill("iron-cloth")) {
                   absorb_skill = victim->query_skill_mapped("iron-cloth");
                        if(!absorb_skill) {
                        absorb_skill = "iron-cloth";
                        }
                        if (eff_ness=SKILL_D(absorb_skill)->effect());
                                else eff_ness=100;
                }
                absorb_vic = 2*victim->query_skill("iron-cloth")*eff_ness/100 +
                                victim->query_temp("apply/iron-cloth");
                if(victim->query_skill("iron-cloth")) {
                        absorb_skill = victim->query_skill_mapped("iron-cloth");
                        if(!absorb_skill) {
                        absorb_skill = "iron-cloth";
                        }
                        inflict_message += SKILL_D(absorb_skill)->query_absorb_msg();
                }
        // -> Debug Message
        //      message_vision("$N's attack absorbed by  "+ SKILL_D(absorb_skill)->name()
        //           + "with, eff_ness " + (string) eff_ness +", absorb_vic: "
        //           +  (string) absorb_vic+".\n", this_player())       ;
        // <- Debug message 
        // damage vs absorb_vic
//              message_vision(" before absorption, damage is "+(string)(damage)+". \n",this_player());
                damage -= absorb_vic;
//              message_vision(" after absorption, damage is "+(string)(damage)+". \n",this_player());
        }
        if(damage <= 0) {
                absorb_skill = victim->query_skill_mapped("iron-cloth");
                if(absorb_skill) {
                        bounce = (SKILL_D(absorb_skill)->bounce_ratio()) * (-damage) / 100;
                        if (objectp(weapon)) {
                                if (weapon->query("skill_type")=="throwing")
                                        bounce = bounce/100;
                                if (weapon->query("skill_type")=="whip")
                                        bounce = bounce/10;
                        }
                        absorb_skill = attacker ->query_skill_mapped("iron-cloth");
                        if(absorb_skill) {
                                bounce -= (SKILL_D(absorb_skill)->bounce_ratio()) * attacker->query_skill("iron-cloth") / 100;
                   }
//                      message_vision(" bounce damage is "+(string)(bounce)+". \n",this_player());
                        if(bounce > 0) {
                                attacker->receive_damage("kee", bounce, victim);
                                inflict_message += damage_msg(bounce, "反弹伤");
                                total_damage=-bounce;
                        }
                }
        } else {
                if(shield=victim->query_temp("shield_force"))
                { 
                                s_type=shield["type"];
                                s_ratio=shield["ratio"];
                                s_msg=shield["msg"];
                                s_force=victim->query(s_type)*s_ratio/100; 
                                if(stringp(s_type))
                                if(s_force>0)
                                if(damage<s_force)
                                        {
                                                victim->add(s_type,-damage*100/s_ratio);
                                                damage=0;
                                                inflict_message+=s_msg;
                                                return damage;
                                        }
                                        else
                                        {
                                                damage-=s_force;
                                                victim->set(s_type,0);
                                        }
                }
                        victim->receive_damage("kee", damage, attacker); 
        // (9) wizard debug information. --- pure kee damage
                if(wizardp(attacker) && (string)attacker->query("env/combat1")=="verbose" ) {
                        tell_object(attacker, sprintf(HIW "DAMAGE:%d\t\n" NOR, damage));
                }
                if(wizardp(victim) && (string)victim->query("env/combat1")=="verbose" ) {
                        tell_object(victim, sprintf(HIY "DAMAGE STATUS:\tYour Kee Damage:%d\t\n" NOR, damage));
                } 
                total_damage = damage;                   //     that's the real damage 
           if((attacker->is_killing(victim)) || weapon) {
                        damage = random(damage);        // that's the eff_damage
                        if(damage > (int)victim->query_temp("apply/armor") ) {
                                victim->receive_wound("kee",
                                                damage - (int)victim->query_temp("apply/armor"), attacker);
                        }
                }
        }  
//      write(" damage is "+(string)(total_damage)+". \n");
//      Here we should report total damage, since it's possible to do a 10000 kee damage
//      while only 10 eff_damage ....  only the first value is useful for players.
        if(bounce<=0||damage>0)
                inflict_message += damage_msg(total_damage, action["damage_type"]);
//      message_vision(" total damage returned is "+(string)(total_damage)+". \n",this_player());
        return total_damage;
} 
// dodge_attack
// the function that checks if the attack can be dodged.
int dodge_attack(object attacker, int ap, mapping action, object victim) {
        int dp;
        string dodge_skill,attack_skill;
        mixed tmp;
        object att_weapon,boot;
        function f; 
        dodge_message = ""; 
        if(objectp(att_weapon=attacker->query_temp("weapon")))
        {
                attack_skill=attacker->query_skill_mapped(att_weapon->query("skill_type"));
                if(attack_skill)
                if(SKILL_D(attack_skill)->undodgeable())
                        return 0;
        }
        else
        {
                attack_skill=attacker->query_skill_mapped("unarmed");
                if(attack_skill)
                if(SKILL_D(attack_skill)->undodgeable())
                        return 0;
        }
// if(victim->query_busy())
//              return 0;
//      message_vision("try dodge\n",victim);
        // victim has no action point
/*      if(!victim->actionOK()) {
                return 0;
        }
*/   
        // Get base dodge power.
        dp = skill_power(victim, SKILL_USAGE_DODGE); 
        // Take into account of attacker's action.
        if(action["dodge"]) {
                dp -= dp * action["dodge"] / 1000 ;
        } 
        // Take into account of victim is busy or not.
        if(victim->is_busy()) {
                dp /= 5;
        } 
        // Debug message
        if(wizardp(attacker) && (string)attacker->query("env/combat1")=="verbose" ) {
                tell_object(attacker, sprintf(HIW "DP:%d\t" NOR, dp));
        }
        // Debug message ends 
        // minimum dp is 1.
        dp = dp > 0 ? dp : 1; 
        // Did the victim dodge the attack?
        if( random(ap + dp) < dp ) {
                // Get dodge messages.
                dodge_skill = victim->query_skill_mapped("dodge");
                if(!dodge_skill) {
                        dodge_skill = "dodge";
                }
                dodge_message = SKILL_D(dodge_skill)->query_dodge_msg();
                if(stringp(tmp = SKILL_D(dodge_skill)->dodge_ob(attacker, victim))) {
                        dodge_message += tmp;
                }
                //我们确定，只有鞋子可以有dodge_ob，要不然就出妖怪了。
                //love
                //10/12/2002

                if(objectp(boot=victim->query_temp("armor/boots")))
                {
                        if(functionp(f=boot->query_temp("dodge_ob",1)))
                        {
                                tmp=evaluate(f,attacker, victim);
                                if(stringp(tmp) )
                                {
                                        parry_message += tmp;
                                }
                        }
                }
                // Give combat_exp for dodge attack.
                if(ap > dp && (!userp(victim) || !userp(attacker))
                                && random(victim->query("gin")*100/victim->query("max_gin")
                                                + victim->query_int())>50) {
                        victim->add("combat_exp", 1);
                        if (victim->query_skill("dodge",1)<200) victim->improve_skill("dodge", 1);
                }
                return dp;
        } else {
                return 0;
        }
} 
// parry_attack
// the function that checks if the atack can be parried.
int parry_attack(object attacker, int ap, mapping action, object victim) {
        string parry_skill;
        mixed tmp;
        int pp;
        object weapon,armor;
        string wptype,pski;
        function f; 
        parry_message = ""; 
        // victim has no action point
/*      if(!victim->actionOK()) {
                return 0;
        }
*/
        // Get parry skill power.
   pp = skill_power(victim, SKILL_USAGE_PARRY);
//      message_vision("do_parry\n",victim);
        // Attacker's action modifier.
        if(action["parry"]) {
                pp -= pp * action["parry"] / 1000 ;
        } 
        // Attacker has a weapon.
        if(objectp(attacker->query_temp("weapon"))) {
                pp /= 2;
        } 
        // If victim is busy...
        if(victim->is_busy()){
                pp -=pp/5;
        }
        ap=ap/2;
        // minimum pp is 1.
        pp = pp > 0 ? pp : 1;
//      message_vision("try parry\n",victim); 
        // Debug message
        if(wizardp(attacker) && (string)attacker->query("env/combat1")=="verbose" ) {
                tell_object(attacker, sprintf(HIW "PP:%d\t" NOR, pp));
        }
        // Debug message ends  
        victim->set_temp("test_ap",ap);
        victim->set_temp("test_pp",pp);
        // Did victim parry the attack?
        if(random(pp+ap)< pp) {
                // Get parry messages.
                if(weapon=victim->query_temp("weapon")){
                        wptype=weapon->query("skill_type");
                        if(pski=victim->query_skill_mapped("parry"))
                        if(SKILL_D(pski)->valid_enable(wptype))
                                parry_skill = pski; 
                        if( !parry_skill)  parry_skill = "parry";
                } else {
                        parry_skill = victim->query_skill_mapped("unarmed");
                        if(!parry_skill) parry_skill = "unarmed";
                }  
                parry_message = SKILL_D(parry_skill)->query_parry_msg(attacker->query_temp("weapon"));

                if(stringp(tmp = SKILL_D(parry_skill)->parry_ob(attacker,victim))) {
                        parry_message += tmp;
                } 
                // 装备上面的parry_ob，我个人以为只能1种。
                // ok，这里，拿着这个武器的人招架了一下，那么可以，没问题
                // love
                // 10/12/2002
                if(objectp(weapon))
                {
                        if(functionp(f=weapon->query_temp("parry_ob",1)))
                        {
                                tmp=evaluate(f,attacker, victim);
                                if(stringp(tmp) )
                                {
                                        parry_message += tmp;
                                }
                        }
                }
                else
                // 嗯，如果右手没兵器，左手拿着一个fist，那么也可以允许用fist来招架
                if(objectp(weapon=victim->query_temp("left_hand")))
                {
                        if(functionp(f=weapon->query_temp("parry_ob",1)))
                        {
                                tmp=evaluate(f,attacker, victim);
                                if(stringp(tmp) )
                                {
                                        parry_message += tmp;
                                }
                        }
                }
                else
                // 看起来，我们可以用一些装备来parry
                // 目前我个人认为可能的装备是：shield,ring,bracelet,
                // 我个人认为这些的parry_ob是不允许并存的，
                // so 1.weapon,2.secondary_weapon,3.shield,4.bracelet,5.ring,
                // 感觉上拿个指环去挡，有点变态。。。。。。算还行吧
                if(objectp(armor=victim->query_temp("armor/shield")))
                {

                        if(functionp(f=armor->query_temp("parry_ob",1)))
                        {
                                tmp=evaluate(f,attacker, victim);
                                if(stringp(tmp) )
                                {
                                        parry_message += tmp;
                                }
                        }
                }
                else
                if(objectp(armor=victim->query_temp("armor/bracelet")))
                {
                        if(functionp(f=armor->query_temp("parry_ob",1)))
                        {
                                tmp=evaluate(f,attacker, victim);
                                if(stringp(tmp) )
                                {
                                        parry_message += tmp;
                                }
                        }
                }
                else
                if(objectp(armor=victim->query_temp("armor/ring")))
                {
                        if(functionp(f=armor->query_temp("parry_ob",1)))
                        {
                                tmp=evaluate(f,attacker, victim);
                                if(stringp(tmp) )
                                {
                                        parry_message += tmp;
                                }
                        }
                }  
                // Give combat_exp for parry attack.
                if(ap > pp && (!userp(victim) || !userp(attacker))
                                && random(victim->query("gin")*100/victim->query("max_gin")
                                                + victim->query_int())>50) {
                        victim->add("combat_exp", 1);
                        if (victim->query_skill("parry",1)<200) victim->improve_skill("parry", 1);

                }
                return pp;
        } else {
                return 0;
        }
} 
// counter_attack
// the function checks if we can counter the attack.
varargs int counter_attack(object attacker, int ap, mapping action, object victim,int i) {
        mapping counter_action,w_action;
        int counterp, damage, counterResult;
        string counter_skill, dodge_skill, tmp,w_name,vw_name;
        object victim_weapon = victim->query_temp("weapon");
        object attacker_weapon=attacker->query_temp("weapon"); 
        counter_message = "";
        // victim is busy or unconcious, can't counter attack.
        if(victim->is_busy() || victim->query_temp("is_unconcious")) {
                return 0;
        }
        // get victim's counter attack action.
        counter_action = get_action(victim, 0);
        if(!mapp(counter_action)) {
                return 0;
        }
        if(i)
                counter_message+=victim->query_temp("counter_msg")+counter_action["action"]+"！\n";
        else
                counter_message += counter_msg[random(sizeof(counter_msg))]
                                + counter_action["action"] + "！\n"; 
        // Get counter attack power
        counterp = skill_power(victim, SKILL_USAGE_ATTACK); 
        // Did victim counter attack?
        if(random(ap +  counterp) < counterp) {
                // Give combat_exp for counter attack.
                if(ap > counterp && (!userp(victim) || !userp(attacker))
                                && random(victim->query("gin")*100/victim->query("max_gin") + victim->query_int())>50) {
                        victim->add("combat_exp", 1);
                        victim->improve_skill("dodge", 1);
                } 

                // NPC have chance to get exp when fail to hit.
                if(!userp(attacker) && random(attacker->query_int()) > 15) {
                        attacker->add("combat_exp", 1);
                }
                damage = attack_damage(victim, counter_action, attacker);
                counter_message += damage_message;
                damage = inflict_damage(victim, attacker, damage, counter_action);
                counter_message += inflict_message;
                if(damage > 0) {
                        attacker_damage += damage;
                } else {
                        victim_damage += -damage;
                }
                counterResult = damage;
        } else {
                dodge_skill = attacker->query_skill_mapped("dodge");
                if(!dodge_skill) {
                        dodge_skill = "dodge";
                }
                counter_message += SKILL_D(dodge_skill)->query_dodge_msg();
                if(stringp(tmp = SKILL_D(dodge_skill)->dodge_ob(attacker, victim))) {
                        counter_message += tmp;
                }
                counterResult = RESULT_DODGE;
        }
        if(objectp(attacker_weapon))
                vw_name=attacker_weapon->name();
        if(objectp(victim_weapon)) {
                w_name=victim_weapon->name();
                w_action=victim_weapon->query_action();
                if(counter_action["post_action"]) {
                        counter_message += call_other(victim_weapon, counter_action["post_action"], victim, attacker, counterResult);
                }
                else if(w_action["post_action"]&&!random(5))
                        result_message += call_other(victim_weapon, w_action["post_action"], attacker, victim, counterResult);
                else
                        counter_message += victim_weapon->wear_off(victim, attacker, counterResult); 
                //-commented out by neon to get rid of the double wear-off
                //counter_message +=  victim_weapon->wear_off(victim, attacker, counterResult);

        } 
        counter_message = prepare_final_message(victim, attacker,w_name, vw_name,counter_action, counter_message);
        counter_message = replace_string(counter_message, "$N", "$TMP");
        counter_message = replace_string(counter_message, "$n", "$N");
        counter_message = replace_string(counter_message, "$TMP", "$n");
        return counterp;
} 
// do_protect()
// a function that checks to see if there is anything/anyone protects our victim
int do_protect(object attacker, int ap, mapping action, object victim) {
        object *pros;
        string output, parry_skill;
        int pp, i, result; 
        pros = victim->query_temp("protectors");
        i = random(sizeof(pros));
        if(!pros[i]) {
                pros -= ({pros[i]});
                if(!sizeof(pros)) {
                        victim->delete_temp("protectors");
                }
                result = 0;
        // Protector
        } else if((environment(pros[i])  != environment(victim))
                        && (environment(pros[i]) != victim)) {
                result = 0;
        } else if(pros[i]->is_character()) {
                // Can't protect other people, if you are busy.
                if(pros[i]->is_busy()){
                        result = 0;
                } else {
                        // Check if the pros[i] can parry this attack for the victim.
                        result = parry_attack(attacker, ap, action, pros[i]);
                        if(result) {
                                protect_message = parry_message;
                                if(objectp(pros[i]->query_temp("weapon"))) {
                                        protect_message = replace_string(protect_message, "$v", (pros[i]->query_temp("weapon"))->name());
                                }
                        }
                }

        } else {
                result = pros[i]->protection();
                protect_message = pros[i]->protection_msg();
        } 
        if(result) {
                protector = pros[i];
                protect_message = replace_string(protect_message, "$n", pros[i]->name());
        }
        return result;
} 
// get_action(object me)
// Return an action the object can take.
mapping get_action(object me, int attack_type) {
        mapping action; 
        action = me->query("actions");
        if(!mapp(action)) {
                me->reset_action();
                action = me->query("action");
                if(!mapp(action)) {
                        CHANNEL_D->do_sys_channel( "sys",
                                        sprintf("%s(%s): bad action = %O", me->name(1),
                                        me->query("id"), me->query("actions", 1)));
                        return 0;
                }
        }
        return action;
} 
// do_attack()
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
int do_attack(object attacker, object victim, int attack_type, mixed att_msg) {
        mapping action,w_action;
        string result,w_name,vw_name;
        int ap, ranCor, counterpower, actionResult, damage;
        object attacker_weapon;
        object victim_weapon; 
        // initial global variables.
        attacker_damage = 0;
        victim_damage = 0;

        result_message = "";  
        // (1) First see if we are capable of attack
/*      if(attacker->query_temp("is_unconcious")
                        || (attack_type != TYPE_PERFORM && !attacker->actionOK()))
                return 0;
*/
        if(!objectp(attacker) || !living(attacker) ||attacker->is_busy()
                        || !objectp(victim) ) return 1; 
        victim->delete_temp("damaged_during_attack"); 
        // (2) Find out what action the attacker will take.
        action = get_action(attacker, attack_type);
        if(!mapp(action)) {
                return 1;
        } 
        attacker_weapon = attacker->query_temp("weapon");
        victim_weapon= victim->query_temp("weapon"); 
        // (3) Prepare AP for the attacker.
        ap = skill_power(attacker, SKILL_USAGE_ATTACK);  
        // Debug message
        if(wizardp(attacker) && (string)attacker->query("env/combat1")=="verbose" ) {
                tell_object(attacker, sprintf(HIW "\nAP:%d\t" NOR, ap));
        }
        // Debug message ends  
        result_message = "\n" + action["action"] + "！\n";
        if(stringp(att_msg)) {
                result_message = "\n" + att_msg + "\n";
        }
        // (4) if player is enforced, let him/her relase the
        //     force even without hit others
        if(userp(attacker)) {
                if(attacker->query("force") > attacker->query("force_factor")/2) {
                        attacker->add("force", -attacker->query("force_factor")/2);
                } else {
                        attacker->set("force_factor", 0);
                }
        } 
        // (5) Let's see what/who can protect our victim, $N, $n,...all applies
        protect_message = "";
        result = "";

        actionResult = RESULT_UNKNOWN;
        counterpower = 0;
        if(sizeof(victim->query_temp("protectors"))) {
                counterpower = do_protect(attacker, ap, action, victim);
                result_message += protect_message;
                actionResult = counterpower > 0 ? RESULT_PROTECT : RESULT_UNKNOWN;
        } 
        // (6) Find out what is the reaction from the victim.
        if(actionResult == RESULT_UNKNOWN&&attack_type!=TYPE_QUICK)
        { 
                // (6.1) Find out if victim can react.
/*              if(living(victim))
                {
                        if(attack_type == TYPE_PERFORM)
                        {
                                ranCor = random(25 + attacker->query_cor());
                        }
                        else
                        {
                                ranCor = random(victim->query_cor() + 25 + attacker->query_cor());
                        } 
                        // (6.2) victim counter attack.
                        if(ranCor > (attacker->query_cor() + 25)) {
                                if(userp(victim)) {
                                        if(victim->query("force") > victim->query("force_factor")) {
                                                victim->add("force", -victim->query("force_factor"));
                                        } else {
                                                victim->set("force_factor", 0);
                                        }
                                }
                                counterpower = counter_attack(attacker, ap, action, victim);
                                result = counter_message;
                                actionResult = RESULT_COUNTER; 
                        // (6.3) victim try to dodge attack
                } else
                if(ranCor > attacker->query_cor()) */  
                                counterpower = dodge_attack(attacker, ap, action, victim);
                                result = dodge_message;
                                actionResult = counterpower > 0 ? RESULT_DODGE : RESULT_UNKNOWN;

                        if(!counterpower)
                        {
                        // (6.4) victim try to parry attack
                                counterpower = parry_attack(attacker, ap, action, victim);
                                result = parry_message;
                                actionResult = counterpower > 0 ? RESULT_PARRY : RESULT_UNKNOWN;
                        }
                        // (6.5) victim try to counter attack
                        if(!counterpower&&victim->query_cor() > random(attacker->query_cor() + 100)
                                &&attack_type==TYPE_REGULAR)
                        {
                                if(userp(victim))
                                {
                                        if(victim->query("force") > victim->query("force_factor"))
                                        {
                                                victim->add("force", -victim->query("force_factor"));
                                        }
                                 else   {
                                                victim->set("force_factor", 0);
                                        }
                                }
                                counterpower = counter_attack(attacker, ap, action, victim);
                                actionResult = counterpower > 0 ? RESULT_COUNTER : RESULT_UNKNOWN;
                                result= counter_message;
                        }
                        else if(victim->query_temp("counter_action"))
                        {
                                counterpower = counter_attack(attacker, ap, action, victim,1);
                                result+= counter_message;
                                victim->delete_temp("counter_action");
                        } 
        }
        // (7) Attack not blocked, take damage.
        if((actionResult == RESULT_UNKNOWN) || (actionResult == RESULT_COUNTER)) {
                victim->set_temp("damaged_during_attack",1);
                damage = attack_damage(attacker, action, victim);
                result_message += damage_message; 
                damage = inflict_damage(attacker, victim, damage, action);
                result_message += inflict_message;

                if(damage < 0) {
                        attacker_damage += -damage;
                } else {
                        victim_damage += damage;
                        actionResult = victim_damage;
                }
        } 
        result_message += result;
        if(objectp(victim_weapon))
                vw_name=victim_weapon->name();
        if(objectp(attacker_weapon)) {
                w_name=attacker_weapon->name();
                w_action=attacker_weapon->query_action();  
                if(actionResult == RESULT_PROTECT) {
                        if(action["post_action"]) {
                                result_message += call_other(attacker_weapon, action["post_action"], attacker, victim, actionResult);
                        }
                        else if(w_action["post_action"]&&!random(5))
                                result_message += call_other(attacker_weapon, w_action["post_action"], attacker, victim, actionResult); 
                        if (objectp(attacker_weapon)) result_message += attacker_weapon->wear_off(attacker, victim, actionResult);
                        else {
                                attacker_weapon = 0;
                                attacker->delete_temp("weapon");
                        } 
                } else {
                        if(action["post_action"]) {
                                result_message += call_other(attacker_weapon, action["post_action"], attacker, victim, actionResult);
                        }
                        else if(w_action["post_action"]&&!random(5))
                                result_message += call_other(attacker_weapon, w_action["post_action"], attacker, victim, actionResult); 
                        if (objectp(attacker_weapon)) result_message += attacker_weapon->wear_off(attacker, victim, actionResult);
                        else {
                                attacker_weapon = 0;
                                attacker->delete_temp("weapon");
                        }
                }
        } 
        // (7) Give experience
        if(userp(attacker) && !userp(victim) ) {

                if((ap < counterpower)
                                && (random(attacker->query("sen")*100/attacker->query("max_sen")) > 50)
                                && (((int)attacker->query_encumbrance()*100/(int)attacker->query_max_encumbrance()) < 20)
                                && damage > 0) {
                        if(random(attacker->query("potential")) < 50000) {
                                attacker->add("potential", 1);
                        }
                        if(random(attacker->query("combat_exp") < 100000)) {
                                attacker->add("combat_exp", 1);
                        }
                }
        }
        // NPC have chance to get exp when fail to hit.
        if(!userp(attacker) && random(attacker->query_int()) > 15) {
                attacker->add("combat_exp", 1);
        } 
        // (8) Prepare final result and status message, and show it.
        result_message = prepare_final_message(attacker, victim,w_name,vw_name, action, result_message);
        message_vision(result_message, attacker, victim);
        if(victim_damage) {
                report_status(victim, (attacker->is_killing(victim)) || (attacker->query_temp("weapon") ) ? 1 : 0);
                //加到这里，造成了damage，才会中断function busy
                if(victim->is_busy())
                        victim->interrupt_me(attacker,"hit");
        }
        if(attacker_damage) {
                report_status(attacker, 0);
        } 
        // (9) wizard debug information.
        if(wizardp(attacker) && (string)attacker->query("env/combat")=="verbose" ) {
                tell_object(attacker, sprintf(GRN "ATTACK STATUS:\tAP: %d\tCP: %d\tVD:%d\tAD:%d\n" NOR,
                                ap/100, counterpower/100, victim_damage, attacker_damage));
        }
        if(wizardp(victim) && (string)victim->query("env/combat")=="verbose" ) {
                tell_object(victim, sprintf(GRN "DEFENSE STATUS:\tAP: %d\tCP: %d\tVD:%d\tAD:%d\n" NOR,
                                ap/100, counterpower/100, victim_damage, attacker_damage));
        }
        //不应该在这里，只有被打中，才会中断function busy
/*

        if(victim->is_busy()) {
                victim->interrupt_me(victim,attacker,"hit");
        } */
/*      if((!attacker->is_killing(victim->query("id")))
                        && (!victim->is_killing(attacker->query("id")))
                        && (attacker->query("kee")*2 <= attacker->query("max_kee")
                                || attacker->query("eff_gin")*2 <= attacker->query("max_gin")
                                || attacker->query("eff_sen")*2 <= attacker->query("max_sen")
                                )
                        ){
                attacker->remove_enemy(victim);
                victim->remove_enemy(attacker);
                message_vision(winner_msg[random(sizeof(winner_msg))], victim, attacker);
// check to see if anything special need to be done after fight for both win/lose.
                fight_reward(victim, attacker);
                fight_penalty(victim, attacker);
        } */ 
        if((!attacker->is_killing(victim->query("id")))
                        && (!victim->is_killing(attacker->query("id")))
                        && (victim->query("kee")*2 <= victim->query("max_kee")
                                || victim->query("eff_gin")*2 <= victim->query("max_gin")
                                || victim->query("eff_sen")*2 <= victim->query("max_sen")
                                )
                        && damage > 0 ) {
                attacker->remove_enemy(victim);
                victim->remove_enemy(attacker);
                if(victim->query_temp("is_unconcious")){ 
                } else {
                        message_vision(winner_msg[random(sizeof(winner_msg))], attacker, victim);
                }
// check to see if anything special need to be done after fight for both win/lose.
                fight_reward(attacker, victim);
                fight_penalty(attacker, victim);
        }  
} 
// since most spell/magic perform don't call combatd fight(), this function needs to
//be called in perform to check winner/loser. 
void win_lose_check(object attacker, object victim, int damage) { 
                if((!attacker->is_killing(victim->query("id")))

                        && (!victim->is_killing(attacker->query("id")))
                        && (victim->query("kee")*2 <= victim->query("max_kee")
                                || victim->query("gin")*2 <= victim->query("max_gin")
                                || victim->query("sen")*2 <= victim->query("max_sen")
                                )
                        && damage > 0 ) {
                attacker->remove_enemy(victim);
                victim->remove_enemy(attacker);
                if(victim->query_temp("is_unconcious")){ 
                } else {
                        message_vision(winner_msg[random(sizeof(winner_msg))], attacker, victim);
                }
                fight_reward(attacker, victim);
                fight_penalty(attacker, victim);
        }
}  
// fight()
// This is called in the attack() defined in F_ATTACK, which handles fighting
// in the heart_beat() of all livings. Be sure to optimize it carefully.
void fight(object me, object victim) {
        object ob; 
        // Check to see if fight can start.
        if(!living(me)
                        || (environment(me) != environment(victim))
                        || (!me->visible(victim) && userp(me) && (random(150 + (int)me->query_skill("perception")) < 100))) {
                return;
        } 
        // victim fight back.
        victim->fight_ob(me); 
        //  If I am too clumsy to attack.
        if (random(me->query_temp("buff/slow"))>=100) {
                message_vision(YEL"\n$N身手一缓，略一迟疑，竟错过了大好的攻击时机。\n"NOR,this_object());
                return;
        } 
        // If victim is unconcious, always take the chance to makeanattack.
        if( victim->query_temp("is_unconcious")) {
                do_attack(me, victim, TYPE_QUICK, 0); 
        // Else, see if we are brave enough to make an aggressive action.
        } else if((int) me->query_cor()*3/2 > random((int) victim->query_cor())||victim->is_busy()) {

                // do normal attack,
                do_attack(me, victim, TYPE_REGULAR, 0);
                // If I have dual-attack skill.
                if (random(me->query_skill("dual-attack",1))>= 100) {
                        message_vision(CYN"\n$N攻势连绵不断，前招未老，后招又已击到。\n"NOR,me);
                        do_attack(me, victim, TYPE_REGULAR, 0);
                }
                // If I am really fast so i can attack again.
                if (random(me->query_temp("buff/haste"))>=100) {
                        message_vision(WHT"\n$N攻势凌厉无匹，瞬间又已攻出一招。\n"NOR,me);
                        do_attack(me, victim, TYPE_REGULAR, 0);
                }
        // Else, we just start guarding.
        } else {
                message_vision(guard_msg[random(sizeof(guard_msg))], me, victim);
        }
        return;
}  
// auto_fight()
// This function is to start an automatically fight. Currently this is
// used in "aggressive", "vendetta", "hatred", "berserk" fight.
void auto_fight(object me, object obj, string type) {
        int bellicosity, fined;
        object silver, gold, cloth, room; 
        if(!me || !obj || (!userp(me) && !userp(obj)) || me->is_fighting(obj) || me->query_temp("is_unconcious")
                        ||!living(me) || environment(me)!=environment(obj)
                        || environment(me)->query("no_fight")) {
                return;
        } 
        if(type == "berserk") {
                bellicosity = (int)me->query("bellicosity");
                message_vision("$N用一种异样的眼神扫视著$n。\n", me,obj);
                if(((int)me->query("force") + (int)me->query_tol() * 10) >
                                (random(bellicosity) + bellicosity)/2 ) {
                        return;
                }
                if(userp(obj) && (int) obj->query("combat_exp") < LOWER_LIMIT) {
                        return;
                }

                if( bellicosity > (int)me->query("score") && !wizardp(obj) ) {
                        message_vision("$N对著$n喝道：" + RANK_D->query_self_rude(me)
                                        + "看你实在很不顺眼，去死吧。\n", me, obj);
                        me->kill_ob(obj);
                        obj->kill_ob(me);
                } else {
                        message_vision("$N对著$n喝道：喂！" + RANK_D->query_rude(obj)
                                        + "，" + RANK_D->query_self_rude(me) +
                                        "正想找人打架，陪我玩两手吧！\n", me, obj);
                        me->fight_ob(obj);
                        obj->fight_ob(me);
                }
        } else if(type == "naked") {
                if(!obj->is_naked()) {
                        return;
                }
                /*
                if (userp(me) && !obj->is_ghost() && me->query("cps") <= obj->query("per"))
                {
                        message_vision("$N睁大眼睛，痴痴的望著$n。\n", me, obj);
                }
                */
                /* old naked code, will fine player 10 silver send player to prison
                message_vision("$N对著$n喝道：喂！你赤身裸体有伤风化，罚银十两！\n", me, obj);
                fined = 0;
                if(silver = present("silver_money",obj)) {
                        if(silver->query_amount() >= 10) {
                                silver->add_amount(-10);
                                fined = 1;
                        }
                }
                if(!fined && gold = present("gold_money",obj)) {
                        gold->add_amount(-1);
                        silver = new("/obj/money/silver");
                        if(silver) {
                                silver->set_amount(90);
                                silver->move(obj);
                        }
                        fined = 1;

                }
                if(fined) {
                        message_vision(RED"$n被$N罚了十两银子！\n"NOR, me, obj);
                        cloth = new("/obj/armor/cloth");
                        if(cloth) {
                                cloth->move(obj);
                                cloth->wear();
                                message_vision("$N对著$n说道：把这件衣服穿上吧。\n", me, obj);
                        }
                } else {
                        obj->set("marks/有伤风化", 1);
                        if(objectp(room = find_object("/d/jinan/pyard"))
                                        || objectp(room = load_object("/d/jinan/pyard"))) {
                                cloth = new("/obj/armor/cloth");
                                if(cloth) {
                                        cloth->set("name", "囚服");
                                        cloth->move(obj);
                                        cloth->wear();
                                        message_vision("$N对著$n说道：没钱？把这件囚服穿上去做工吧。\n", me, obj);
                                }
                                obj->move(room);
                        }
                }
                */
        } else {
                if(type=="hatred")
                {
                        message_vision(catch_hunt_msg[random(sizeof(catch_hunt_msg))],me,obj);
                        me->kill_ob(obj);
                }
                else
                if(type=="vendetta")
                {
                        if(userp(me)&&me->query("combat_exp")<obj->query("combat_exp"))
                                return;
                        message_vision(catch_hunt_msg[random(sizeof(catch_hunt_msg))],me,obj);
                        me->kill_ob(obj);
                        obj->kill_ob(me);       // since "me" is NPC, it doesn't matter add_killer or just kill_ob;
                }

                else
                {
                        message_vision(catch_hunt_msg[random(sizeof(catch_hunt_msg))],me,obj);
                        me->kill_ob(obj);
                }
        }
} 
void auto_follow(object follower, object leader) {
        int fexp, lexp;
        fexp = (follower->query("combat_exp") > 0? follower->query("combat_exp") : 0);
        lexp = (leader->query("combat_exp") > 0 ? leader->query("combat_exp") : 0);
        if( random(lexp) > fexp/10 ) {
                follower->set_leader(leader);
        } else {
                follower->set_leader(0);
        }
} 
// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event) {
        switch(event) {
                case "dead":
                        if (ob->query("death_msg")) message_vision(ob->query("death_msg"),ob); //可以加一句临死前的话。
                        message_vision("\n$N死了。\n\n", ob);
                        break;
                case "unconcious":
                        message_vision("\n$N脚下一个不稳，跌在地上一动也不动了。\n\n", ob);
                        break;
                case "revive":
                        message_vision("\n$N慢慢睁开眼睛，清醒了过来。\n\n", ob);
                        break;
        }
} 
void winner_reward(object killer, object victim) {
        object owner; 
        if(owner=killer->query("possessed")) {
                killer = owner;
        }
        killer->defeated_enemy(victim);

} 
void loser_penalty(object killer, object victim) {
        object owner; 
        if(owner=victim->query("possessed")) {
                victim = owner;
        }
        victim->defeated_by_enemy(killer);
} 
void killer_reward(object killer, object victim) {
        int bls, i;
        string vmark;
        object owner;
        object env;
        object *mem;
        object realkiller;
        mapping quest; 
        // Call the mudlib killer apply.
        realkiller = killer;
        if(owner=killer->query("possessed")) {
                killer = owner;
        }
        killer->killed_enemy(victim);
        if(userp(victim) ) {
                if((int) killer->query("combat_exp") < (int)victim->query("combat_exp")/10 * 9) {
                        killer->set("last_good_kill",(int)killer->query("mud_age"));
                }
                env = environment(victim);
                if((objectp(env)) && !(env->query("no_death_penalty")))
                        killer->add("PKS", 1);
                bls = 10;
        } else {
                killer->add("MKS", 1);
                bls = 1;
        } 
        // NPC got 10 times of bellicosity than user.
        //      killer->add("bellicosity", bls * (userp(killer)? 1: 2));
        // --- to stop exploit, NPC will not gain bellicosity anymore, silencer, 12/23/2001 
        if (userp(killer))
                killer->add("bellicosity",bls); 

        // Now official killing official will also become fei.
        if((!userp(victim)) && stringp(vmark = victim->query("vendetta_mark"))
                        /*&& vmark != killer->query("vendetta_mark")*/) {
                killer->add("vendetta/" + vmark, 1);
        } 
        // Now let's add the quest reward here 
        mem = pointerp(killer->query_team()) ? killer->query_team() : ({ killer });
        if (!userp(victim))
        for(i=0; i<sizeof(mem); i++) {
                if ((mem[i])) {
                        if(mapp(quest = mem[i]->query("quest"))
                                && (string)victim->name() == quest["quest"]
                                && (time() - mem[i]->query("task_time") <= 900)) {
                                QUESTS_D->give_reward(mem[i],killer, quest);
                        }
                }
        } 
        // let's add the hired killer things here
        if(!userp(realkiller) && realkiller->query("hired_killer")
                        && (string)victim->query("id") == (string)realkiller->query("haunttar")) {
                message_vision("$N一拱手：幸不辱使命！后会有期！\n",realkiller);
                destruct(realkiller);
        }
} 
varargs void victim_penalty(object victim, mixed killer,int flag) {
        string msg="莫名其妙地死了。";
        mapping actions;
        object env;
        int combat_exp, combat_pot,combat_exp_old,combat_pot_old;
        int combat_exp_lost,combat_pot_lost;
        string special_death_place,death_msg; 
        if( userp(victim)) {
                env = environment(victim);
                if((objectp(env)) && (env->query("no_death_penalty"))) {
                        victim->set_temp("no_death_penalty",1);
                        victim->clear_all_condition();  //In yaren fight, easilly get posioned.
                        return;
                }
                if(objectp(killer))

                {
                        msg="被"+killer->query("name");
                        actions = killer->query("actions");
                        switch(actions["damage_type"])
                        {
                                case "拉伤":
                                case "割伤":
                                        msg+="砍死了。";
                                        break;
                                case "刺伤":
                                        msg+="刺死了。";
                                        break;
                                case "瘀伤":
                                        msg+="击死了。";
                                        break;
                                case "抓伤":
                                        msg+="抓死了。";
                                        break;
                                case "反弹伤":
                                        msg+="震死了。";
                                        break;
                                default:
                                        msg+="杀死了。";
                        }
                }
                else if(stringp(killer))
                        msg = killer;//这里，我们给予一个可以变化死亡出的info的机会
                if(!flag)
                CHANNEL_D->do_sys_channel(
                                "info",sprintf("%s(%s)"+msg, victim->name(1),victim->query("id")));
                // Add/Set/Reduce flags.
                victim->add("KILLED",1);
                victim->clear_all_condition();
                victim->set("bellicosity", 0); 
                // Setup for some dungeons with low death penalty.
                if (objectp(killer))
                if (special_death_place=killer->query("dungeon_npc")) {
                        if (special_death_place=="eren2"
                                && domain_file(file_name(environment(victim)))=="eren2"){

                                if (victim->query("marks/万春流")) victim->add("combat_exp",-2000);
                                        else victim->add("combat_exp",-4000);
//                              if (victim->query("potential") - victim->query("learned_points")>100)
                                victim->add("potential",-40);
                                return;
                                }
                }  
                // Add/Set/Reduce flags.
                victim->delete("vendetta");
                if( victim->query("thief") )
                        victim->set("thief", (int)victim->query("thief") / 2); 
                // Give the death penalty based on combat experince.
                combat_exp = victim->query("combat_exp");
                combat_exp_old=combat_exp;
                combat_pot = victim->query("potential") - victim->query("learned_points");
                combat_pot_old=victim->query("potential");
                if(combat_pot < 0) {
                        combat_pot = 0;
                } 
                if(combat_exp < 20000) {
                        victim->add("combat_exp", -(int)(combat_exp * 2 / 100)); 
                //} else if(combat_exp < 100000) {
                //      victim->add("combat_exp", -(int)(combat_exp * 2 / 100));
                //      victim->add("potential", -(int)(combat_pot * 25 / 100)); 
                } else if(combat_exp < 200000) {
                        victim->add("combat_exp", -(int)(combat_exp * 2 / 100));
                        victim->add("potential", -(int)(combat_pot * 25 / 100)); 
                } else if(combat_exp < 1000000) {
                        victim->add("combat_exp", -(int)(combat_exp * 2 / 100));
                        victim->add("potential", -(int)(combat_pot * 25 / 100)); 
                } else {
                        victim->add("combat_exp", -(int)(combat_exp * 2 / 100));
                        victim->add("potential", -(int)(combat_pot * 50 / 100)); 
                }
                victim->skill_death_penalty(combat_exp); 
//      Codes below are set for possible revive skills;
                if (combat_exp>1000000) combat_pot_lost = combat_pot*50/100;
                        else if (combat_exp>20000)      combat_pot_lost=combat_pot*25/100;
                        else combat_pot_lost=0;

                combat_exp_lost=combat_exp_old-victim->query("combat_exp");
                if (combat_exp_lost<0) combat_exp_lost=0;
                if (combat_pot_lost<0) combat_pot_lost=0;
                victim->set("death/time",time());
                victim->set("death/exp_lost",combat_exp_lost);
                victim->set("death/pot_lost",combat_pot_lost);
        }
} 
