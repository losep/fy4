 // modified by mimicat@fy4
#include <ansi.h>        
inherit SKILL;
void setup(){
        set("name", "雪影剑法");
        set("usage/sword", 1);
        set("usage/parry", 1);
        set("effective_level", 150);
        set("learn_bonus", 30);
//      set("black_white_ness", 0);
//      set("practice_bonus", 0);
        set("skill_class", "taoist");
        
        set("parry_msg", ({
        "$n剑尖向上，以“朝天一柱香”格开了$N的$w。\n",
        "结果$n用手中的$v格开了$N的$w。\n",
        "$n滑出一步，$v“横云断峰”斜扫敌腰。\n",
        "$n不退反进，竟走险招，和身下扑，$v直刺，点向$N右脚。\n",
        "$n右肩侧过，“彩虹经天”，$v上撩，化解了$N的攻势。\n",
        "$n镇定自若，“流星堕地”，直立向下挡架。\n",
        }) ); 
        set("unarmed_parry_msg", ({
        "$n将手中的$v舞得密不透风，封住了$N的攻势。\n",
        "$n滑出一步，$v“横云断峰”斜扫敌腰。\n",
        "$n不退反进，竟走险招，和身下扑，$v直刺，点向$N右脚。\n",
        "$n右肩侧过，“彩虹经天”，$v上撩，化解了$N的攻势。\n",
        "$n镇定自若，“流星堕地”，直立向下挡架。\n",
        }) );
        action = ({
                ([      "action":               "$N使一招「回光幻电」，手中$w幻一条疾光刺向$n的$l",
                        "dodge":                -20,
                        "damage":               130,
                        "damage_type":  "刺伤"
                ]),
                ([      "action":               "$N使出雪影剑法中的「风霜碎影」，$w连挥剑光霍霍斩向$n的$l",
                        "dodge":                -20,
                        "damage":               130,
                        "damage_type":  "割伤"
                ]),
                ([      "action":               "$N一招「残阳照雪」，纵身飘开数尺，手中$w斩向$n的$l",
                   "dodge":                -30,
                        "damage":               120,
                        "damage_type":  "割伤"
                ]),
                ([      "action":               "$N手中$w中宫直进，一式「冰谷初虹」对准$n的$l刺出一剑",
                        "dodge":                -40,
                        "damage_type":  "刺伤"
                ]),
                ([      "action":               "$N纵身一跃，手中$w一招「长空雷隐」对准$n的$l斜斜刺出一剑",
                        "dodge":                -40,
                        "damage_type":  "刺伤"
                ]),
                ([      "action":               "$N的$w凭空一指，一招「断石狼烟」刺向$n的$l",
                        "dodge":                20,
                        "damage":               140,
                        "damage_type":  "刺伤"
                ]),
        });
}
int valid_learn(object me)
{
        object ob; 
        if( (int)me->query("max_force") < 50 ){
                return notify_fail("你的内力不够，没有办法练雪影剑法。\n");
        }
        if(!::valid_learn(me)){
                return 0;
        }
        return 1;
} 
int practice_skill(object me)
{
        if((int)me->query("force") < 5 ){
                return notify_fail("你的内力或气不够，没有办法练习雪影剑法。\n");
        }
        if(!::practice_skill(me)){
                return 0;
        }
        me->add("force", -5);
        write("你按著所学练了一遍雪影剑法。\n");
   return 1;
}  
mixed hit_ob(object me, object victim)
{
        object weapon;
        string result;
        int extra;
         
        weapon=me->query_temp("weapon");
        extra=weapon->query("exorcising");
        if(!extra)
                return ;
        result=HIR"符纸上的血色似乎又加深了一分。。。\n";
        if(victim->is_ghost())
        {       victim->set("eff_sen",-100);
                result+=HIR+victim->name()+"凄厉的惨叫了一声，化为了灰烬。\n"NOR;
        }
        else if(victim->is_zombie())
        {
                victim->set("eff_sen",-100);
                result+=HIR+victim->name()+"凄厉的惨叫了一声，化为了一滩血水。\n"NOR;
        }
        else
        {
                victim->receive_wound("sen",extra,me);
                victim->add("sen",-extra/2);
                result+=HIY+victim->name()+"浑身有如雷击，神为之夺。\n"NOR;
        }
        return result;
}
                
int undodgeable()
{
        return this_player()->query("no_dodge_snow");
}  
