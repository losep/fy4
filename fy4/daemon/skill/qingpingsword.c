 // qingpingsword.c
#include <ansi.h>
inherit SKILL;
void setup(){
        set("name", "清平剑法");
        set("usage/sword", 1);
        set("usage/parry", 1);
        set("skill_class", "shenshui");
        set("effective_level", 220);
        set("learn_bonus", 10);
        set("practice_bonus", -5);
        set("black_white_ness", 5);
        set("parry_msg", ({
        "$n使出一招「凤舞九天」，手中的$v化作一条长虹，磕开了$N的$w。\n",
        "$n使出「封」字诀，将$N的$w封于丈外。\n",
        "$n使出一招「朝朝瑞雪」，手中的$v化做漫天雪影，荡开了$N的$w。\n",
        "$n手中的$v一抖，一招「旱地春雷」，向$N拿$w的手腕削去。\n",
        }) ); 
        set("unarmed_parry_msg", ({
        "$n将手中的$v舞得密不透风，封住了$N的攻势。\n",
        "$n反手一招「阳光普照」，整个人消失在一团剑光之中。\n",
        "$n使出一招「龙舞九天」，$v直刺$N的双手。\n",
        "$n将手中的$v化做七条剑气，迫得$N连连后退。\n",
        }) );
        action = ({
        ([      "action":               
"$N使一招「峰回路转」，手中$w如一条银蛇般刺向$n的$l",
                "dodge":                20,
                "damage":               80,
                "force":                200,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N使出清平剑法中的「空山鸟语」，剑光霍霍斩向$n的$l",
                "dodge":                20,
                "damage":               120,
                "force":                100,
                "damage_type":  "割伤"
        ]),
        ([      "action":               
"$N一招「御风而行」，身形陡然滑出数尺，手中$w斩向$n的$l",
                "dodge":                30,
                "damage":               80,
                "force":                100,
                "damage_type":  "割伤"
        ]),
        ([      "action":               
"$N手中$w中宫直进，一式「旭日东升」对准$n的$l刺出一剑",
                "dodge":                40,
                "damage":               70,
                "force":                60,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N纵身一跃，手中$w一招「金光泻地」对准$n的$l斜斜刺出一剑",
                "dodge":                40,
                "damage":               100,
                "force":                60,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N的$w凭空一指，一招「童子引路」刺向$n的$l",
                "dodge":                20,
                "damage":               150,
                "force":                120,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N手中$w向外一分，使一招「柳暗花明」反手对准$n$l一剑刺去",
                "dodge":                20,
                "damage":               110,
                "force":                180,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N横剑上前，身形一转手中$w使一招「空谷秋虹」画出一道光弧斩向$n的$l",
                "dodge":                30,
                "damage":               80,
                "force":                110,
                "damage_type":  "割伤"
        ]),
        });
}
int valid_learn(object me)
{ 
    if( (int)me->query("max_force") < 50 ){
        return notify_fail("你的内力不够，没有办法练清平剑法。\n");
        }
    if(me->query_skill("qingpingforce",1)+40<me->query_skill("qingpingsword",1)){
        return notify_fail("你的清平内功不够火候。\n");
        }
        if(!::valid_learn(me)){
                return 0;
        }
    return 1;
} 
int practice_skill(object me)
{
    if((int)me->query("force") < 10 ){
        return notify_fail("你的内力或气不够，没有办法练习清平剑法。\n");
    }
    if(!::practice_skill(me)){
        return 0;
    }
    me->add("force", -10);
    write("你按著所学练了一遍清平剑法。\n");
    return 1;
} 
mixed parry_ob(object victim,object me)
{
        int mylvl,extra ;
        string msg;
        mylvl=me->query_skill("nine-moon-force",1);
        if (extra=me->query_temp("nine-moon-force_poison"))
        {
                victim->receive_wound("kee",extra/3,me);
                victim->add("kee",-extra/3);
                if (!victim->query_temp("weapon"))      return MAG"$N只觉触手处紫气一闪，缕缕阴寒锥心而至！\n"NOR;
                        else return MAG"$N只觉一层淡淡的紫气从兵刃上蔓延而来，刺骨的寒气几乎令手腕转动不灵。\n"NOR;
                
           return msg;
        }
} 
