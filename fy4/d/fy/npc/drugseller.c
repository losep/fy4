 // tea_waiter.c
inherit NPC;
inherit F_VENDOR; 
void create()
{
        set_name("卖药的", ({ "medseller" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long",
                "一个普生堂的卖药的的伙计\n");
        set("combat_exp", 5);
        set("chat_chance", 2);
        set("chat_msg", ({
                "卖药的高叫道：喔～～～云南白药～～\n",
                "卖药的高叫道：喔～～～虎骨丸～～\n",
                "卖药的高叫道：喔～～～大风丸～～\n",
                "卖药的叫道：您哪，知道沥泉之水吗？喝了沥泉水，百毒不侵呐！\n",
                "卖药的叫道：我这里的药，都是用沥泉水精炼而出的，别的地方您哪找去！\n", 
        }) ); 
        set("attitude", "friendly");
        set("vendor_goods", ([
                __DIR__"obj/sendrug":11,
                __DIR__"obj/keedrug":30,
                __DIR__"obj/gindrug":11,
        ]) );
        setup();
        carry_object("/obj/armor/cloth")->wear(); 
} 
void init()
{
        add_action("do_vendor_list", "list");
}     
