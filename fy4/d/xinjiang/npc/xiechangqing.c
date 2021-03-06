 inherit NPC;
#include <ansi.h>
int kill_him(); 
void    smart_fight(); 
void create()
{
        set_name("谢长卿", ({ "xie changqing" }) );
        set("gender", "男性");
        set("age", 25);
        set("long",
"一个年轻而英俊的少年，他甚至在颤抖着，英俊的面庞上，也蒙着
一层死灰之色。。\n"
);
      
        set("chat_chance", 1);
        set("chat_msg", ({
"谢长卿喃喃道：“我还年轻，我不能就这样无声无息地死去，而且那时
谷中再无他人，即使我作了昧心之事，又有谁会传将出去，唉！我想
人人都该为自己打算吧。”\n",
        }) ); 
        set("inquiry", ([
            "梅山民" : (: kill_him :),
            "mei shanmin" : (: kill_him :),
             ]));
        set("fly_target",1); 
        set("attitude", "friendly");
        set("title",HIG"点苍"NOR);
        set("nickname", HIG"落英剑"NOR);
        set("score", 0);
        set("reward_npc", 1);
        set("difficulty",2);
        set("class","legend");
        
        set("combat_exp", 3500000);        
        set("int", 30);
        set("cps", 20);
        set("spi", 30);
        set("fle",60);
        set("per",40);
        set("str",40);
        
        set("force", 1000);
        set("max_force",1000);
        set("force_factor", 90);
        set("atman", 1000);
        set("max_atman", 1000);
        set("mana", 500);
        set("max_mana", 500);
        
        set("resistance/kee",40);
        set("resistance/gin",40);
        set("resistance/sen",40);
        
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: smart_fight() :),              
        }) );
          
        set_skill("move", 200);
        set_skill("force", 200);
        set_skill("spells", 150);
        set_skill("unarmed", 150);
        set_skill("sword", 200);
        set_skill("parry", 150);
        set_skill("dodge", 150);
        set_skill("magic",150);
                
        set_skill("qidaoforce", 150);
        set_skill("fall-steps",150);
        set_skill("meihua-shou",150);
        set_skill("diesword",150);
        
        map_skill("unarmed","meihua-shou");
        map_skill("force", "qidaoforce");
        map_skill("dodge","fall-steps");
        map_skill("move","fall-steps");
        map_skill("parry","diesword");
        map_skill("sword","diesword");
        
        set_temp("apply/dodge", 30);
        set_temp("apply/armor", 30);
        setup(); 
        add_money("gold", random(5));
        carry_object("/obj/weapon/sword")->wield();
        carry_object("/obj/armor/cloth")->wear();
} 
 
smart_fight()
{
        int i;
        object *enemy;
        enemy = this_object()->query_enemy();
        i = sizeof(enemy);
        while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        if (!enemy[i]->is_busy() && random(3)
                                && enemy[i]->query("combat_exp")<10*this_object()->query("combat_exp")) {
                                this_object()->smart_busy();
                        }
                        if (!this_object()->is_busy()) {
                                this_object()->smart_attack();
                        } 
                }
        }
} 
smart_busy() {
        command("unwield sword");
        this_object()->perform_action("unarmed.meihai");
        command("wield sword");
        return;
}
smart_attack() {
        this_object()->perform_action("sword.caidiekuangwu");
        return;
} 
int kill_him()
{
        object me;
        me = this_player();
        if (this_object()->is_fighting()) return 1;
        message_vision(CYN"谢长卿怔了半晌说:此是我平生最憾之事....\n"NOR,this_object());
        message_vision(CYN"谢长卿突然扬起手中长剑，凝视片刻，陡然挥剑“擦”的一声，声响未歇，
剑交左手，又是“擦”的一声。只见他双手鲜血淋漓，两只大姆指跌落地上，他
用中食两指夹着长剑奋力一掷，“落英剑”化作一圈流光直飞而出，“扑”的一
声钉在树干上，剑柄带着小半截剑身左有摇震晃荡，接着头也不回的去了。\n"NOR,this_object());
        me->set("marks/谢长卿",1);
        destruct(this_object());
        return 1;
} 
