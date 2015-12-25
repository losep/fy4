#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int target_perform(object me, object target); 
int perform(object me, object target)
{
    string msg;
    int extra,i,j,lmt,damages,bell;
    object weapon;
    object *enemy;
    
    extra = me->query_skill("sharen-sword",1);
    if ( extra < 100)
        return notify_fail("你的杀人剑法还不够纯熟！\n");
        
    enemy=me->query_enemy();
    if(!sizeof(enemy))
                return notify_fail("［杀人如麻］只能对战斗中的对手使用。\n"); 
    if (me->query("bellicosity")<=100 && userp(me))
                return notify_fail("你的杀气不够高。\n");    
    
    if (target && me->query_temp("jingxing/concentrate")) {
        if( !target->is_character()
                || !me->is_fighting(target) )
                return notify_fail("［杀人如麻］只能对战斗中的对手使用。\n");   
///     message_vision(" aaa.\n",me);
        target_perform(me,target);
        return 1;
    }
                
    if(target)  return notify_fail("［杀人如麻］不需要指定使用对象！！\n");
    
    if (me->query_temp("timer/sharen")+20>time() && userp(me) 
                && ! me->query_temp("jingxing/concentrate"))
                return notify_fail("你的杀气还需过一段时间才能重新聚集起来\n");
        
    weapon = me->query_temp("weapon");
    if(extra <= 162)
    {
        damages = extra/4;
        msg = HIY"$N"+HIY"凶性大发，手中的"+ weapon->name()+
            HIY"狂风暴雨般地向$n"+HIY"卷来! " NOR;
        message_vision(msg,me,enemy[0]);
        me->add_temp("apply/attack",damages);
        me->add_temp("apply/damage",damages*2);
    }
    else
    {
        if (me->query("class")=="assassin") damages = extra/3;
                else {damages = extra/4;}
        
        msg = HIY"$N"+HIY"杀气大盛，只见"NOR+ weapon->name()+
            HIY"疾风骤雨般地向$n"+HIY"全身各大要穴刺到! " NOR;
        message_vision(msg,me,enemy[0]);
        me->add_temp("apply/attack",damages);
        me->add_temp("apply/damage",damages*2);
    }
    lmt = random(5)+3;
        if (extra>160 && lmt<5) lmt=5;
         
    j=0;
    for(i=1;i<=lmt;i++)
    {
        msg =  HIR "第"+chinese_number(i)+"剑！" NOR;
        COMBAT_D->do_attack(me,enemy[j],TYPE_PERFORM,msg);
        if (j==sizeof(enemy)-1) j=0;
                        else j++;
    }
    me->add_temp("apply/attack",-damages);
    me->add_temp("apply/damage",-damages*2);
    if (me->query("combat_exp")>2500000)  bell= (me->query("combat_exp")-2500000)/20000;
    bell = lmt+bell;
    if (bell>100) bell = 100;
    if (userp(me)) me->add("bellicosity",-bell);
    if (me->query_busy()<3) 
                me->start_busy(3);
    me->set_temp("timer/sharen",time());
    return 1;
}  
int target_perform(object me, object target)
{
    string msg;
    int extra,i,j,lmt,damages,bell;
    object weapon;
    object *enemy;
            
    extra = me->query_skill("sharen-sword",1);
    weapon = me->query_temp("weapon");
    if(extra <= 162)
    {
        damages = extra/4;
        msg = HIY"$N"+HIY"凶性大发，手中的"+ weapon->name()+
            HIY"狂风暴雨般地向$n"+HIY"卷来! " NOR;
        message_vision(msg,me,target);
        me->add_temp("apply/attack",damages);
        me->add_temp("apply/damage",damages*2);
    }
    else
    {
        if (me->query("class")=="assassin") damages = extra/3;
                else {damages = extra/4;}
        
        msg = HIY"$N"+HIY"杀气大盛，只见"NOR+ weapon->name()+
            HIY"疾风骤雨般地向$n"+HIY"全身各大要穴刺到! " NOR;
        message_vision(msg,me,target);
        me->add_temp("apply/attack",damages);
        me->add_temp("apply/damage",damages*2);
    }
    lmt = random(5)+3;
    if (extra>160 && lmt<5) lmt=5;
         
    for(i=1;i<=lmt;i++)
    {
        msg =  HIR "第"+chinese_number(i)+"剑！" NOR;
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);  
    }
    
    me->add_temp("apply/attack",-damages);
    me->add_temp("apply/damage",-damages*2);  
    
    if (userp(me)) me->add("bellicosity",-30);
    if (me->query_busy()<4) 
                me->start_busy(4);
    return 1;
} 
