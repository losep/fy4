#include <ansi.h>
inherit SKILL;
void setup(){
        set("name", "短歌刀法");
        set("usage/blade", 1);
        set("usage/parry", 1);
        set("practice_damage", 30);
        set("effective_level", 200);
        set("learn_bonus", -100);
        set("practice_bonus", -5);
        set("practice_limit",190);
        set("black_white_ness", 10);
        set("skill_class", "legend");
        
        set("parry_msg", ({
        "$n使出一招「唯有杜康」，用手中的$v急削$N的五指。\n",
                "$n左脚踏前一步，一招「青青子衿」，手中的$v从侧面飘向$N之必救。\n",
                "$n手中的$v一抖，挽出一片刀花，一招「悠悠我心」，撒向$N的全身。\n",
                "$n微退一步，手中的$v划出一条光弧，一招「但为君故」，将$N的全身围住。\n",
        }) ); 
        set("unarmed_parry_msg", ({
                "$n使出一招「沉吟至今」，用手中的$v急砍$N。\n",
                "$n左脚踏前踏，一招「呦呦鹿鸣」，手中的$v挥向$N之必救。\n",
                "$n手中的$v一抖，一招「山不厌高」，奔向$N。\n",
                "$n手中的$v划出一招「天下归心」，将$N的全身围住。\n",
        }) );   
        action = ({
                ([      "action":               "$N使一招「对酒当歌」，手中$w风似地向$n的$l斩去！",
                        "damage":               100,
                 "force":               50,
                        "dodge":                70,
                        "damage_type":  "割伤"
                ]),
                ([      "action":               "$N弯刀似月，$w随著一招「人生几何」由下而上撩往$n的$l",
                        "damage":               400,
                 "force":               50,
                        "damage_type":  "割伤"
                ]),
                ([      "action":               "$N身形一转，一招「譬如朝露」$w如朝露闪烁，斩向$n的$l",
                        "damage":               40,
            "force":               50,
                        "damage_type":  "割伤"
                ]),
                ([      "action":               "$N舞动$w，一招「去日苦多」往$n的$l斜斜砍出一刀",
                 "force":               50,
                        "damage_type":  "割伤"
                ]),
                ([      "action":               "$N手中$w一晃，一招「慨当以慷」迅捷无伦地劈向$n的$l",
                 "force":               50,
                        "damage":               100,
                        "damage_type":  "割伤"
                ]),
                ([      "action":               "$N提气丹田，身型咋展，一招「忧思难忘」直劈$n$l",
                        "damage":               60,
                 "force":               50,
                        "damage_type":  "割伤"
                ]),
                ([      "action":               "$N移步侧身，使一招「何以解忧」刀光霍霍斩向$n的$l",
                        "damage":               80,
                 "force":               50,
                        "damage_type":  "割伤"
                ]),
        });
}
int valid_learn(object me)
{
    if( (int)me->query("max_force") < 100 ){
        return notify_fail("你的内力不够，没有办法练短歌刀法。\n");
        }
    if( (string)me->query_skill_mapped("force")!= "qidaoforce"){
        return notify_fail("短歌刀法必须配合铁雪内功才能练。\n");
        }
    if(!::valid_learn(me)){
        return 0;
    }
    return 1;
} 
mixed hit_ob(object me, object victim, int damage_bonus)
{
    object ob;
    if( random(damage_bonus) < 300 ) return 0;
    if(ob=victim->query_temp("weapon"))
    if(ob->query("skill_type") == "sword")
    if(victim->query_skill_mapped("sword") == "deisword" )
    if(me->query_skill("blade") > victim->query_skill("sword")) {
    switch(random(3)) {
            case 0:
                    message_vision(HIR "\n因武功路数相克，$N占尽了上风！" NOR,me,victim);
                    break;
            case 1:
                    message_vision(HIR "\n$N轻而易举地抢入$n的空隙之间！" NOR,me,victim);
                    break;
            case 2:
                    message_vision(HIR "\n因刀剑相克，$n逐渐施展不开了！" NOR,me,victim);
                    break;
                    }
    return random(me->query_skill("blade")) * 4;
    }
    return 0;
} 
int practice_skill(object me)
{
        if((int)me->query("force") < 10 ){
                return notify_fail("你的气或内力不够，不能练短歌刀法。\n");
        }
        if(!::practice_skill(me)){
                return 0;
        }
        me->add("force", -10);
        return 1;
}      
