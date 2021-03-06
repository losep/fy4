 // earth-warp.c
#include <ansi.h>
#include <command.h>
#include <login.h> 
inherit F_CLEAN_UP; 
int scribe(object me, object sheet, string arg)
{
        object newsheet;
        string err;
        if(me->query("class")!="taoist")
                return notify_fail("只有三清宫弟子才可以画符。\n");
   
        if((int)me->query_skill("scratmancy",1) < 100 )
                return notify_fail("你的符之术不够高！\n"); 
        if( sheet->name() != "桃符纸" )
                return notify_fail("天师斩鬼符要画在桃符纸上！\n"); 
        if( (int)me->query("mana") < 200 ) 
                return notify_fail("你的法力不够了！\n");
        if( me->query("sen")<300)
                return notify_fail("你现在神智不是很清楚，无法画符。\n"); 
        sheet->add_amount(-1);
        seteuid( geteuid(me));
        newsheet = new("/obj/item/magic_seal");
        newsheet->set_name(YEL "天师斩鬼符" NOR, 
                ({ "exorcise sheet", "sheet"}) );    
        newsheet->set("burn_func", (: call_other, __FILE__, "do_warp":));
        newsheet->move(me);
        me->add("mana", -150);
//      me->receive_wound("sen", 50);
        me->save();
        message_vision("$N写了一道天师斩鬼符。\n" NOR, me);
        return 1;
} 
int do_warp(object sheet)
{
        object me,weapon;
        int extra, exp_bonus;
        
        me=this_player();
        if(me->query("class")!="taoist")
           return notify_fail("只有三清宫弟子才能够祭天师斩鬼符。\n"); 
        weapon=me->query_temp("weapon");
        if(!weapon||!weapon->query("for_taoist"))
                return notify_fail("祭天师斩鬼符必须有相应的法器配合才行。\n"); 
        if(me->query_skill_mapped("sword")!="snowshade-sword")
                return notify_fail("祭天师斩鬼符必须有雪影剑法相配合。\n"); 
        extra=me->query_skill("snowshade-sword",1);
        if (extra<120)
                return notify_fail("你雪影剑法的修为还不够高深，无法使用天师斩鬼符。\n");
        if(weapon->query("exorcising"))
                return notify_fail("这把剑已经被施过法力了。\n"); 
        me->start_busy(1);
        message_vision(BLU"$N祭起一张天师斩鬼符，手持桃木剑，使出雪影剑法，口中念念有词。。。\n",me);
        message_vision(HIW"$N手中桃木剑望空一指，已将符咒挑于剑尖！！\n\n",me);
        message_vision(HIR"符纸竟转为殷红，血色映照在在场每个人的脸上！！\n"NOR,me);
        weapon->set("name","挑着一张符纸的桃木剑");
        exp_bonus = me->query_skill("scratmancy",1);
        extra = extra/4 + exp_bonus;
        extra = extra*3 + random(extra);
        weapon->set("exorcising",extra);
        call_out("remove_effect",exp_bonus,weapon);
        return 1;
}
int remove_effect(object weapon)
{
        object holder;
        
        if(!weapon)
                return 1;
        holder=environment(weapon);
        if(!holder)
                return 1;
        if(interactive(holder)) 
                message_vision(CYN"桃木剑尖上的符纸转为黑色，慢慢破碎散落了。\n"NOR,holder);
        else    
                message("vision",CYN"桃木剑尖上的符纸转为黑色，慢慢破碎散落了。\n"NOR,holder);
        weapon->delete("exorcising");
        weapon->set("name","桃木剑"); 
        return 1;
}
       
