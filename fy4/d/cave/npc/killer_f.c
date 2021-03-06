 inherit NPC;
#include <ansi.h> 
void create()
{
        set_name("井木犴", ({ "killer f" }) );
        set("title",HIC"青龙杀手"NOR);
        set("gender", "男性" );
        set("age", 42);
        set("long",
                "此人黑布蒙面，在漆黑的坑道中只有兵刃在闪光。\n");
        set("attitude", "friendly");
        set("combat_exp", 1400000);
        set("attitude", "friendly");
        set("class","bat");
        set("force",1000);
        set("max_force",1000);
        set("force_factor",30);
        
        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: perform_action, "whip.tianleiyiji" :),
        }) ); 
        set_skill("flame-strike",120);
        set_skill("move", 100);
        set_skill("force", 100);
        set_skill("spells", 100);
        set_skill("unarmed", 100);
        set_skill("sword", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("gouyee", 100);
        set_skill("whip",100);
        set_skill("thunderwhip",150);
        set_skill("zuixian-steps",160);
        set_skill("cursism", 100);
        set_skill("necromancy", 100);     
        map_skill("spells", "necromancy");
        map_skill("force", "gouyee");
        map_skill("whip","thunderwhip");
        map_skill("dodge","zuixian-steps");
        map_skill("parry","thunderwhip");
        map_skill("move","zuixian-steps");
        map_skill("unarmed","flame-strike"); 
        setup();
        
        carry_object("/obj/armor/cloth")->wear();
        carry_object("/obj/weapon/whip")->wield();
}    
int heal_up()
{
        if( environment() && !is_fighting() ) {
                call_out("leave", 1);
                return 1;
        }
        return ::heal_up() + 1;
} 
void leave()
{
        message("vision",
                HIW + name() + "一闪身，在黑暗中消失了。\n" NOR, environment(),
                this_object() );
        destruct(this_object());
}  
void init()
{
    object ob;
    ::init();
    if( interactive(ob = this_player()) && !is_fighting() ) 
    {
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
    }
} 
void greeting(object ob)
{   
        string where, location;
        if( !interactive(ob) || environment(ob) != environment() )
                return;
        if (!ob->query("vendetta/authority") ){
                this_object()->kill_ob(ob);
                   ob->kill_ob(this_object());
        }
        return;
}  
