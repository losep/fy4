 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors. 
#include <ansi.h>
inherit NPC; 
void create()
{
        set_name("老板娘", ({ "boss" }) );
        set("gender", "女性" );
        set("age", 52);
        set("long",
                "老板娘善长补衣服，补出来的衣服又牢固而且不难看。\n");
        set("combat_exp", 50);
        set("str",20);
        set("attitude", "friendly");
        setup();
        carry_object("/obj/armor/cloth")->wear(); 
} 
void init()
{       
        object ob; 
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_bu","bu");
} 
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "老板娘笑道：这位" + RANK_D->query_respect(ob)
                                + "，你的衣衫看起来好象要补一下了。\n");
                        break;
                case 1:
                        say( "老板娘说道：这位" + RANK_D->query_respect(ob)
                                + "，你的衣衫都被人砍破了，来补一下吧。\n");
                        break;
   }
} 
int  do_bu(string arg)
{
        object me, ob;
        object gold;
        int cost = 1;
        int i,j,base,current;
        string id,name ;        
        string file,newfile,filestring;
        me = this_player();
        id = me->query("id");
        if( !arg ) return notify_fail("你要补什麽衣物？\n");
        gold = present("gold_money", this_player());
        if( !gold) return notify_fail("你身上没有金子。\n");
        if( !objectp(ob = present(arg, me)) )
        return notify_fail("你身上没有这样东西。\n");
        if(me->is_busy())
        return notify_fail("你上一个动作还没有完成。\n");
        if( !ob->query("armor_prop") )
        return notify_fail("你只能补穿在身上的东西。\n");
        if( ob->query("equipped") )
        return notify_fail("你不可补正穿着的衣物。\n");
        if( !ob->query("owner") )
        return notify_fail("你只可补自己订的衣物。\n");
        base= (int)ob->query("base_armor");
        seteuid(ROOT_UID);
        current = (int) ob->query("armor_prop/armor");
        for(j=1;j<=100;j++)
        {
                base = base + j;
                if(base >= current) break;
        }
        for(i=1; i<= j;i++)
                        cost = cost * 2;
        if((int) gold->query_amount() < cost)
        return notify_fail("你身上没带够" + sprintf("%d",cost)+ "两金子。\n");
        gold->add_amount(-cost);
        me->start_busy(1);
        ob->add("armor_prop/armor",j);
   ob->set("weight",(int)ob->query("weight")+j*50);
        ob->save();
        ob->restore();
        if(ob->move(me))        
        message_vision("$N拍了拍"+ob->name()+"，说道：好了！\n",this_object());
        seteuid(getuid());
        return 1;
}     
