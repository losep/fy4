 // mystsword.c
#include <ansi.h> 
inherit SKILL;
void setup(){
        set("name", "小步玄剑");
        set("usage/sword", 1);
        set("usage/parry", 1);
        set("effective_level", 70);
        set("learn_bonus", 40);
        set("practice_bonus", 20);
        set("black_white_ness", 30); 
        set("parry_msg", ({
        "结果$n用手中的$v格开了$N的$w。\n",
        }) ); 
        set("unarmed_parry_msg", ({
        "$n将手中的$v舞得密不透风，封住了$N的攻势。\n",
        }) );   
        action = ({
        ([      "name":                 "暮雪三叹",
                "action":               "$N使一招「暮雪三叹」，手中$w急如骤雨般地刺向$n$l",
                "dodge":                -30,
                "damage":               60,
                "damage_type":  "刺伤"
        ]),
        ([      "name":                 "处子弄笛",
                "action":               "$N身形一晃，一招「处子弄笛」向$n$l刺出一剑",
                "dodge":                -20,
                "damage":               80,
                "damage_type":  "刺伤"
        ]),
        ([      "name":                 "阳谷白练",
                "action":               "$N舞动$w，一招「阳谷白练」挟著闪闪剑光刺向$n的$l",
                "dodge":                -40,
                "damage_type":  "刺伤"
        ]),
        ([      "name":                 "薰容逐电",
                "action":               "$N手中$w一个圈转，使出「薰容逐电」中锋直进刺向$n的$l",
                "dodge":                -30,
                "damage":               100,
                "damage_type":  "刺伤"
        ]),
        });
}
int valid_learn(object me)
{ 
    if( (int)me->query_skill("mystforce",1) < 30 ){
        return notify_fail("你的步玄心法火候还不够。\n");
        }
    if( (int)me->query("max_force") < 100 ){
        return notify_fail("你的内力不够，没有办法练小步玄剑。\n");
        }
        if(!::valid_learn(me)){
                return 0;
        }
    return 1;
} 
int practice_skill(object me)
{
    if((int)me->query("force") < 5 ){
        return notify_fail("你的内力或气不够，没有办法练习小步玄剑。\n");
    }
    if(!::practice_skill(me)){
        return 0;
    }
    me->add("force", -5);
    write("你按著所学练了一遍小步玄剑。\n");
    return 1;
}   
