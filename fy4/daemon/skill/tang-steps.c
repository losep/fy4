 // tang-steps.c 唐门千秋步
inherit SKILL;
void setup(){
        set("name", "唐门千秋步");
        set("usage/dodge",1);
        set("usage/move", 1);
        set("effective_level", 150);
        set("learn_bonus", -20);
        set("practice_bonus", -10);
        set("black_white_ness", 30);
        set("skill_class", "tangmen");
        set("dodge_msg", ({
                "$n漫不经心的向左迈出一步，刚好避过$N的凌厉攻势。\n",
                "可是$n恰巧往右走了一步，躲过了$N这一招。\n",
                "只见$n一招「白鹤冲天」，身体向上笔直地纵起丈余，躲过了$N这一招。\n",
                "$n一个「鹞子翻身」，向后纵出数丈之远，避开了$N的凌厉攻势。\n",
                "$n使出「大鹏展翅」，向一旁飘然纵出，轻轻着地。\n"
        "但是$n身形飘忽，轻轻一纵，早已避开。\n",
       "$n身随意转，倏地往一旁挪开了三尺，避过了这一招。\n",
        "可是$n侧身一让，$N这一招扑了个空。\n",
        "却见$n足不点地，往旁窜开数尺，躲了开去。\n",
        "$n身形微晃，有惊无险地避开了$N这一招。\n"
        }) );
} 
int valid_learn(object me)
{
        if( (int)me->query("max_force") < 100 )
                return notify_fail("你的内力不够，没有办法练唐门千秋步。\n"); 
        return 1;
}       
