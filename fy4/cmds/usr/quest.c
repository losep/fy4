 // quest.c
// Copyright (C) 1995 - 2001, by FengYun Workshop. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
//
        
#include <ansi.h>
inherit F_CLEAN_UP;
int time_period(int timep, object me);
int main(object ob, string arg) {
        int i, nowtime = time();
        object me;
        object* mem;
        if(!arg || !wizardp(ob)) {
                me = this_player();
        mem = pointerp(me->query_team()) ? me->query_team() : ({ me }); 
        for(i=0; i<sizeof(mem); i++) {
                if (mem[i]) {
                    if (mem[i] != me) {
                        if(mapp(mem[i]->query("quest"))) {
                                mapping quest;
                                quest =  mem[i]->query("quest");
                                tell_object(me, WHT"队伍成员 "+ mem[i]->name() + WHT" 现在的任务是: " + quest["quest_type"] + "『"NOR + quest["quest"] + NOR WHT"』。\n"YEL);
                                nowtime = (int)time() - mem[i]->query("task_time");
                                if(nowtime  < 900) {
                                        time_period(nowtime, me);
                                } else 
                                        write(YEL"但是"+ mem[i]->name() +"已经没有足够的时间来完成它了。\n"NOR);
                        }
                    }
                }
        }   
    if(!me->query("quest")) {
        if((me->query("next_time")) > time()) {
                    return notify_fail(HIW"你要过" 
                + QUESTS_D->wait_period(me->query("next_time") - time()) 
                + "之后才可要任务。\n"NOR);
        }
        else {
            return notify_fail(NOR"你现在没有任何任务！\n");            
            }
    }
         
        if(mapp(me->query("quest"))) {
                mapping quest;
                quest =  me->query("quest");
                write(NOR"\n你现在的任务是" + quest["quest_type"] + "『" + quest["quest"] + "』。\n");
        } else {
                string quest;
                quest =  me->query("quest");
                write("你现在的任务是关于" + quest+ "。\n");
        }
        nowtime = (int)time() - me->query("task_time");
        if(nowtime  < 900) {
                time_period(nowtime, me);
        } else {
                write(NOR"但是你已经没有足够的时间来完成它了。\n");
                me->set("quest", 0 );
                return notify_fail("这个任务自动取消了。\n");
        }
        } else {
         if(!(ob = present(arg, environment(ob))) && !(ob =  find_player(arg))) {
                return notify_fail("你要察看谁的任务？\n");
        }
        if(!ob->query("quest")) {
                return notify_fail(ob->name()+"现在没有任何任务！\n");
        }
        
        if(mapp(ob->query("quest"))) {
                mapping quest;
                quest =  ob->query("quest");
                write(ob->name()+"现在的任务是" + quest["quest_type"] + "『" + quest["quest"] + "』。\n");
        } else {
                string quest;
                quest =  ob->query("quest");
                write(ob->name()+"现在的任务是关于" + quest+ "。\n");
        }
        nowtime = (int)time() - ob->query("task_time");
        if(nowtime  < 900) {
                time_period(nowtime, this_player());
   } else {
                return notify_fail("但是"+ob->name()+"已经没有足够的时间来完成它了。\n");
        }
        }       
        return 1;
} 
int time_period(int timep, object me) {
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;
        
        if(d) time = chinese_number(d) + "天";
        else time = "";
        
        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";
        tell_object(me,"任务已经开始了" + time + "。\n");
        return 1;
} 
int help(object me) {
        write(@HELP
指令格式 : quest
 
这个指令可以显示出你当前的任务。
HELP);
        return 1;
}    
