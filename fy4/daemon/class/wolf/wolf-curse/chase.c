 // chase.c
#include <ansi.h> 
inherit SSERVER; 
int curse(object me, object target)
{
        string targetname;
        object room,ob;
        int skill,atman,perp;
        
        if(me->query("class")!="wolfmount")
                return notify_fail("只有狼山弟子才能使出「蹑降」。\n");
        
        if( me->is_fighting() )
                return notify_fail("战斗中无法使用这个降头术！\n");
 
        if( me->query("kee") <= 100 )
                return notify_fail("你的气血不够！\n"); 
        if( (skill=me->query_skill("wolf-curse",1)) < 100 )
            return notify_fail("你的降头术不够高深！\n"); 
        if( !(ob=me->query_temp("chase_target")))
                return notify_fail("你没有下过蹑降或者你下蹑降的人已经死了。\n");
        
        if (environment(ob)->query("no_fight")||environment(ob)->query("no_magic")
                ||environment(ob)->query("no_death_penalty"))
                        return notify_fail("那个地方好像受到神灵的保护。\n"); 
        if ( environment(me)->query("no_fly") || environment(ob)->query("no_fly"))
                return notify_fail("此地不能使用蹑降。\n");
        
        if( me->is_ghost())
                return notify_fail("鬼魂无法使用蹑降！\n");     
        
        if(! ob->is_character())
                return notify_fail("追踪这个东西？你是不是觉得很无聊？\n"); 
        
        if( ob->is_ghost())
                return notify_fail("人鬼殊途，你不能追踪！\n"); 
        
        me->receive_damage("kee", 100);
        
        if( random(me->query("combat_exp")/20*skill) <ob->query("combat_exp"))
           {
                 message_vision( HIW "$N神色肃然，口中念念有词，但什么事也没发生。\n" NOR, me);
                 return notify_fail("你的降头术还不够熟练。\n");        
                }
                        
        if (environment(ob)->query("no_fight")||environment(ob)->query("no_magic")||environment(ob)->query("no_fly"))
                return notify_fail("那个地方好像受到神灵的保护.\n");
                
        if (me->query_temp("in_chase"))
                return notify_fail("你已经在追踪对方了");
        
        message_vision( HIW "$N神色肃然，口中念念有词，身影渐渐地模糊起来 ....\n" NOR, me);
        me->set_temp("in_chase");
        room = environment(ob);
        me->start_busy(2); 
        perp=ob->query_skill("perception",1);
        if (perp/10>random(10)|| random(5)) tell_object(ob,HIW"你只觉得一股阴冷的杀意从你身后袭来。\n"NOR);
        
        me->start_call_out( (: call_other, __FILE__, "iam_coming", me,ob,room:), 6);
        return 1;
}  
void iam_coming(object me,object ob,object room)
{
        
        string id_enemy;
        int eff_shen,shen,skill;
        if (me->is_ghost()) {
                tell_object(me,YEL"你怎么成了鬼了，鬼是无法追踪人的！\n"NOR); 
                me->delete("in_chase");
                return;
                } 
                
        me->move(room); 
        message( "vision", HIW "\n忽然一股青烟从地上冒出，"+me->query("name")+"从烟雾中出现！\n\n" NOR,
                room, ({ me }) );
        if ( environment(ob) != environment(me)) {
                        tell_object(me,HIW"太可惜了,"+ob->name()+"刚从这里离开.\n"NOR);
                        return;
                }
        shen=ob->query("sen");
   eff_shen=ob->query("eff_sen");
        if (shen>eff_shen/2+100 && random(me->query("combat_exp"))*10>ob->query("combat_exp"))          
                ob->receive_damage("sen", shen/2, me);
        me->delete("in_chase");
        me->start_busy(2);
        ob->kill_ob(me);
        me->kill_ob(ob);        
}        
