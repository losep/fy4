 // weitianpeng.c
#include <ansi.h> 
inherit NPC; 
void create()
{
        set_name("石秀云", ({ "shi xiuyun","shi" }) );
        set("gender", "女性" );
        set("title", "峨嵋派 侠女" );
        set("nickname", HIM"三英四秀之"NOR );
        set("long",
"一个看上去最文静的女孩子，似乎什么事都会脸红，什么人都不敢抬眼去看。\n"
                );
        set("attitude", "peaceful");
        set("age", 22);
        set("cps", 40);
        set("int", 50);
        set("per", 40);
        set("cor", 40);
        set("agi", 30);
        set("combat_exp", 200000);
        
        set("force", 500);
        set("max_force", 500);
        set("mana", 1000);
        set("max_mana", 1000);
        set("force_factor", 10);
        set("inquiry",  ([
                "叶孤城" : "哦，叶城主的剑法真的是天下第一么？不知道和西门比怎么样？\n",
                "master ye" : "哦，叶城主的剑法真的是天下第一么？不知道和西门比怎么样？\n",
                  "西门吹雪" :"嘻嘻，似乎三姐对这个冷血家伙。。\n",
                  "master ximen" :"嘻嘻，似乎三姐对这个冷血家伙。。\n",
                  "花满楼" : "嗯，真希望能再见到他。他。。\n",
                  "hua manlou" : "嗯，真希望能再见到他。他。。\n",
        ])                      );
       set_temp("apply/armor",50);
        set_temp("apply/attack", 50);
        set("chat_chance", 1);
        set("chat_msg", ({
                "石秀云幽幽道：花公子若是也在，该有多好啊。\n",
                }) ); 
        set_skill("sword", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("move", 100);
                
        setup(); 
        carry_object("/obj/weapon/sword")->wield();
        add_money("gold",1);
        carry_object("/d/fugui/npc/obj/w_skirt4")->wear();
}      
