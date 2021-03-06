 // logind.c
#include <ansi.h>
#include <command.h>
#include <login.h> 
inherit F_DBASE;
int wiz_lock_level = WIZ_LOCK_LEVEL;
int new_user_lock = NEW_USER_LOCK;
string L_IP = "216.101.216.5";
string Rname;
string *banned_name = ({
        "你", "你", "我", "他", "她", "它", "它",
        "风云","阿铁", "风云ＩＩ","风云Ⅱ", "汉族",
        "苗族",  "满族","蒙古族","风云ＩＩＩ","风云Ⅲ",
        "系统", "核心", "系统核心", "风云Ⅳ", "风云ＩＶ",
        "操", "日", "ｆｕｃｋ","ＦＵＣＫ","Ｆｕｃｋ",
});
string *banned_id= ({
        "chat", "new", "fy", "rumor", "tell", "none", "reboot",
        "shutdown","core", "fymud","mud", "fuck", "public", "tianji",
        "afa", "amao", "mei", "huang",  "dick",  "shit","cao","cunt","slut",
        "master", "all", "tufei", "peng" ,
}); 
string *start_loc = ({
        AREA_FY"fqkhotel",
        AREA_CHENXIANG"cag",
        AREA_GUANWAI"inn",
        AREA_LAOWU"inn",
}); 
string *national = ({
        "汉族",
        "苗族",
        "满族",
        "蒙古族",
}); 
private void get_encoding(string arg, object ob);
private void get_id(string arg, object ob);
private void read_msg(string arg, object ob);
private void get_resp(string arg, object ob);
private void confirm_id(string yn, object ob);
private object make_body(object ob);
private int valid_wiz_login(string id,string ip);
private void init_new_player(object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
int check_legal_password(object ob,string arg);
int set_attribute(object user,int tol, int fle, int agi, int dur, int intt, int str, int con, int spi, int per, int cor, int cps, int kar);
int cphirdir(string dirstr, string newdirstr);
string random_name();
void logon_write(string str); 
void create() {
        seteuid(getuid());
} 
void logon(object ob) { 
        // Before we do all this, see if this installation is legal and not expired
/*
        if(SECURITY_D->check_illegal(L_IP)) {
                shutdown(0);
        }
        if(SECURITY_D->check_illegal2()) {
                shutdown(0);
        } 
*/
        if (BAN_D->is_banned(query_ip_name(ob))  ||
                        BAN_D->is_banned(query_ip_number(ob))) {
                write("对不起，您的地址被拒绝连线。\n"
                "请ＥＭＡＩＬ：ｒｏｏｔ＠ｆｅｎｇｙｕｎ．ｃｏｍ陈诉。\n");
                destruct(ob);
                return;
        } 
        cat(WELCOME) ;
        get_encoding("", ob);
} 
private void get_encoding(string arg, object ob) {
        string str;
        object *usr;
        int i, wiz_cnt, ppl_cnt, login_cnt; 
   if(arg == "0" || arg == "０") {
                ob->set_temp("char_encoding", "gb");
        } else if(arg == "1" || arg == "１") {
                ob->set_temp("char_encoding", "big5");
        } else {
                str = "国标码";
                write("    0) " + str + "(" + ENCODE_D->gbTobig5(str) + ") GB\n");
                str = "大五码";
                write("    1) " + str + "(" + ENCODE_D->gbTobig5(str) + ") BIG5\n");
                str = "请选择您使用的内码";
                write(str + "(" + ENCODE_D->gbTobig5(str) + "): ");
                input_to((: get_encoding :), ob);
                return;
        }
        write("\n\n");
        UPTIME_CMD->main();
        usr = users();
        wiz_cnt = 0;
        ppl_cnt = 0;
        login_cnt = 0;
        for(i=0; i<sizeof(usr); i++) {
                if( !environment(usr[i]) ) login_cnt++;
                else if( wizardp(usr[i]) ) wiz_cnt++;
                else ppl_cnt++;
        }
        write(sprintf(BLU"目前共有%s位人士正在游戏中。\n"
        "其中有%s位管理员、%s位本地玩家、及%s位尝试者。\n\n" NOR,
        chinese_number(WHO_D->query_num()), chinese_number(wiz_cnt),
        chinese_number(ppl_cnt), chinese_number(login_cnt))); 
        write("您的英文名字：");
        input_to( (: get_id :), ob);
} 
private void get_id(string arg, object ob)
{
        object ppl,*usr;
        int i; 
        arg = lower_case(arg);
        if( !check_legal_id(arg))
        {
           write("您的英文名字：");
                input_to("get_id", ob);
                return;
        }
#ifdef MAX_USERS
        if( (string)SECURITY_D->get_status(arg)=="(player)"
                && sizeof(users()) >= MAX_USERS ) 
        {
                ppl = find_body(arg);
                // Only allow reconnect an interactive player when MAX_USERS exceeded.
                if( !ppl || !interactive(ppl) )
                {
                        write("对不起，"+MUD_NAME+"的使用者已经太多了，请待会再来。\n");
                        destruct(ob);
                        return;
                }
        }
#endif 
        if( wiz_level(arg) < wiz_lock_level )
        {
                write("对不起，" + MUD_NAME +
                          "目前正在维护之中，请稍候再连线。\n");
                destruct(ob);
                return;
        } 
        if( (string)ob->set("id", arg) != arg )
        {
                write("Failed setting user name.\n");
                destruct(ob);
                return;
        }
// toomany guets nowdays
        if( arg=="guesttttttttt" )
        {
                // If guest, let them create the character.
                confirm_id("Yes", ob);
                return;
        }
        else if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 )
   {
                if( ob->restore() )
                {
                        write("此英文名字已被使用，请输入此帐号的密码：");
                        input_to("get_passwd", 1, ob);
                        return;
                }
                write("您的人物储存挡出了一些问题，请利用 guest 人物通知巫师处理。\n");
                destruct(ob);
                return;
        }
        if(new_user_lock)
        {
                write("现在风云不接受新的人物，请稍候再创造新的人物。\n");
        destruct(ob);
        return;
        }
        usr = filter_array(children(LOGIN_OB), (: interactive :));
        i = sizeof(usr);
        while (i--)
                if (usr[i] != ob && usr[i]->query("id") == arg)
                        break;
        if (i >= 0) {
                write("有其他玩家正在使用这个 ID，请重新输入。\n");
                write("您的英文名字：");
                input_to("get_id", ob);
                return;
        }
        write("使用 " + (string)ob->query("id") +
                  "\n这个名字将会创造一个新的人物，您确定吗(y/n)？");
        input_to("confirm_id", ob);
} 
private void get_passwd(string pass, object ob)
{
        string my_pass;
        object user; 
        write("\n");
        my_pass = ob->query("password");
        if( crypt(pass, my_pass) != my_pass )
   {
                write("密码错误！\n");
                log_file("ATTEMPT_LOGIN",sprintf("FAILED: %s tried to login from %s\n",
                                                                                 ob->query("id"), query_ip_name(ob)));
                destruct(ob);
                return;
        } 
        // Check if we are already playing.
        user = find_body(ob->query("id"));
        if (user)
        {
                if(!user->query_temp("successful_login")) {
                        destruct(user);
                } else { 
                if( user->query_temp("netdead") )
                {
                        reconnect(ob, user);
                        return;
                } 
                write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
                input_to("confirm_relogin", ob, user);
                return;
                }
        } 
        if( objectp(user = make_body(ob)) )
        {
                if( user->restore() )
                {
                        log_file( "USAGE", sprintf(
                                "%s loggined from %s (%s)\n",
                                user->query("id"),query_ip_name(ob), ctime(time()) ) );
                        log_file("STAT", sprintf(
                                "ON %s %s %d %d %d %d %d %d %s\n",
                                user->query("id"),user->query("name"),
                                user->query("combat_exp"), user->query("deposit"),
                                user->query("potential"),user->query("TASK"),
                                user->query("mud_age"), user->query("QUEST"),
                                ctime(time()) ) );
                        if(time()-(int)user->query("kickout_time") < 3600)
                   {
                                write("你现在没有进入风云的权利，请一小时后再联线。\n");
                                destruct(user);
                                destruct(ob);
                                return;
                        }
                        enter_world(ob, user);
                        return;
                }
                else  destruct(user);
        }
        write("请您重新创造这个人物。\n");
        confirm_id("y", ob);
} 
private void confirm_relogin(string yn, object ob, object user)
{
        object old_link; 
        if(!objectp(user)) {
                write("另一个连线中的相同人物已不存在，请从新连线。\n");
                destruct(ob);
                return;
        } 
        if(yn=="") {
                write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
                input_to("confirm_relogin", ob, user);
                return;
        } 
        if(yn[0]!='y' && yn[0]!='Y') {
                write("好吧，欢迎下次再来。\n");
                destruct(ob);
                return;
        } else {
                tell_object(user, "有人从别处( " + query_ip_name(ob)
                                        + " )连线取代你所控制的人物。\n");
                log_file("USAGE", sprintf("%s replaced by %s (%s)\n",
                                                                   user->query("name"),
                                                                   query_ip_name(ob), ctime(time()) ) );
        } 
        // Kick out tho old player.
   old_link = user->query_temp("link_ob");
        if( old_link )
        {
                exec(old_link, user);
                destruct(old_link);
        } 
        reconnect(ob, user);
} 
private void confirm_id(string yn, object ob)
{
        if( yn=="" )
        {
                write("使用这个名字将会创造一个新的人物，您确定吗(y/n)？");
                input_to("confirm_id", ob);
                return;
        } 
        if( yn[0]!='y' && yn[0]!='Y' )
        {
                write("好吧，那麽请重新输入您的英文名字：");
                input_to("get_id", ob);
                return;
        } 
        write( @TEXT
风云Ⅳ是一个以古龙小说为背景的世界，请您想一个有气质，
有个性，又不会太奇怪的中文名字，特别要提醒您的是，
请勿使用古龙小说中的人名。这个名字将代表你的人物，
而且往後将不能再更改，请务必慎重。 
如果你有困难输入中文名字，请直接敲回车键［ＲＥＴＵＲＮ］。
TEXT
                );
        write("您的中文名字：");
        input_to("get_name", ob);
} 
private void get_resp(string arg, object ob)
{
        if( arg=="" )
   {
                write("您满意(y)不满意(n)这个中文名字？");
                input_to("get_resp", ob);
                return;
        } 
        if( arg[0]=='y' || arg[0]=='Y' )
        {
                printf("%O\n", ob);
                ob->set("name", Rname);
                write("请设定您的密码：");
                input_to("new_password", 1, ob);
        return;
        }
        else if( arg[0]=='n' || arg[0]=='N')
        {
                Rname = random_name();
                write("您满意(y)不满意(n)这个中文名字？");
                printf( HIY" -- %s ："NOR, Rname);
                input_to("get_resp", ob);
                return;
        }
        else
        {
                write("对不起，您只能选择满意(y)不满意(n)： ");
                input_to("get_resp", ob);
                return;
        }
} 
private void get_name(string arg, object ob)
{
        string name;
        if( arg =="")
        {
        Rname = random_name();
                write("看来您要个随机产生的中文名字．．\n");
                write("您满意(y)不满意(n)这个中文名字？");
                printf( HIY" -- %s ："NOR, Rname);
                input_to("get_resp", ob);
        }
   else
        {
                if(ob->query_temp("char_encoding") == "big5") {
                        arg = ENCODE_D->big5Togb(arg);
                }
                if( !check_legal_name(arg) )
                {
                        write("您的中文名字：");
                        input_to("get_name", ob);
                        return;
                } 
                printf("%O\n", ob);
                ob->set("name", arg);
                write("请设定您的密码：");
                input_to("new_password", 1, ob);
        }
} 
private void new_password(string pass, object ob)
{
        write("\n");
        if( !check_legal_password(ob,pass))
        {
                input_to("new_password", 1, ob);
                write("请设定您的密码：");
                return;
        }
        ob->set("password", crypt(pass,0) );
        write("请再输入一次您的密码，以确认您没记错：");
        input_to("confirm_password", 1, ob);
} 
private void confirm_password(string pass, object ob)
{
        string old_pass;
        write("\n");
        old_pass = ob->query("password");
        if( crypt(pass, old_pass)!=old_pass ) {
                write("您两次输入的密码并不一样，请重新设定一次密码：");
                input_to("new_password", 1, ob);
                return;
   } 
        write("您的电子邮件地址：");
        input_to("get_email",  ob);
} 
private void get_email(string email, object ob)
{
        object user;
        ob->set("email", email); 
        // If you want do race stuff, ask player to choose one here, then you can
        // set the user's body after the question is answered. The following are
        // options for player's body, so we clone a body here.
        ob->set("body", USER_OB);
        if( !objectp(user = make_body(ob)) )
                return; 
        write("您要扮演男性(m)的角色或女性(f)的角色？");
        input_to("get_gender", ob, user);
} 
private void get_gender(string gender, object ob, object user)
{
        if( gender=="" )
        {
                write("您要扮演男性(m)的角色或女性(f)的角色？");
                input_to("get_gender", ob, user);
                return;
        } 
        if( gender[0]=='m' || gender[0]=='M' )
                user->set("gender", "男性");
        else if( gender[0]=='f' || gender[0]=='F' )
                user->set("gender", "女性" );
        else
        {
                write("对不起，您只能选择男性(m)或女性(f)的角色：");
                input_to("get_gender", ob, user);
                return;
        }
        write("
０．汉族
１．苗族
２．满族
３．蒙古族
\n");
        write("请选择你在风云Ⅳ中的民族（0，1，2，3）：");
        input_to("get_nresp",ob, user);
} 
private void get_nresp(string arg, object ob, object user)
{
        if( arg=="" )
        {
                write("请选择你在风云Ⅳ中的民族（0，1，2，3）：");
                input_to("get_nresp", ob, user);
                return;
        }
        if( arg[0]=='0' || arg[0]=='1' || arg[0]=='2'|| arg[0]=='3')
        {
                log_file( "USAGE", sprintf("%s was created from %s (%s)\n",
                                                                   user->query("id"),
                                                                   query_ip_name(ob), ctime(time()) ) );
        user->set("national",national[(int) (arg[0]-'0')]);
                init_new_player(user);
                enter_world(ob, user);
        return;
        }
        else
        {
                write("对不起，您只能从（0,1,2,3）中选择： ");
                input_to("get_nresp", ob,user);
                return;
        }
} 
object make_body(object ob)
{
        string err;
        object user;
        int n; 
        user = new(ob->query("body"));
        if(!user)
        {
                write("现在可能有人正在修改使用者物件的程式，无法进行复制。\n");
           write(err+"\n");
                return 0;
        }
        seteuid(ob->query("id"));
        export_uid(user);
        export_uid(ob);
        seteuid(getuid());
        user->set("id", ob->query("id"));
        user->set_name( ob->query("name"), ({ ob->query("id")}) );
        return user;
} 
private void init_new_player(object user)
{
        string national;
        user->set("title", "普通百姓");
        user->set("birthday", time() );
        user->set("potential", 299);
        national = user->query("national");
        switch(national)
        {
        case "汉族":
// 汉族 high int, high per, low cor, low tol
                set_attribute(user,5,10,10,10,12,10,10,10,20,10,10,10);
                break;
        case "苗族":
//苗族 high agi, high kar, low con, low spi
                set_attribute(user,10,10,20,10,10,10,5,5,10,15,10,20);
                break;
        case "满族":
//满族 high cps, spi, low int,dur
                set_attribute(user,10,10,10,5,8,10,10,20,10,15,20,10);
                break;
        case "蒙古族":
//蒙古族 high str, fle , low agi, dur
                set_attribute(user,10,20,5,5,10,20,10,10,10,15,10,10);
                break;
        } 
        user->setup();
        user->set("food", user->max_food_capacity());
   user->set("water", user->max_water_capacity());
        user->set("env/wimpy", 50);
        user->set("combat_exp",2000);
        user->set("channels", ({ "chat","fy","new","info",
                                                         "vote","bangtalk","teamtalk" }) );
} 
varargs void enter_world(object ob, object user, int silent)
{
        object cloth, room;
        mixed info;
        string id;
        string mailfile;
        int laston;
        user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
        exec(user, ob);
        user->set_temp("char_encoding", ob->query_temp("char_encoding")); 
        write(CLR + "目前权限：" + wizhood(user) + "\n");
        user->setup(); 
        // add here:
        if ( wizardp(user))
        {// add by akuma for wiz login ip check
             if( valid_wiz_login( user->query("id"),query_ip_number(user) )==0 )
             {
                write("该帐号使用了不被允许的IP登陆，如有疑问，请mailto:admin@fengyun.com，谢谢各位巫师的合作。\n");
                destruct(ob);
                destruct(user);
                return;
             }
        }
        // In case of new player, we save them here right aftre setup
        // compeleted. 
        user->autosave();
        ob->save(); 
        cloth = new("/obj/armor/cloth");
        if(objectp(cloth)) {
                cloth->move(user);
                cloth->wear();
        }
   if(!silent )
        {
                cat(MOTD);
        id = user->query("id");
        mailfile = DATA_DIR+ "user/" + sprintf("%c",id[0]) + "/" + id + "/mail.o";
        if( file_size(mailfile) > 0 )
                        info = stat(mailfile);
        if( info && (int)info[0] >=0 )
                {
                        laston = (int) ob->query("last_on");
                        if( laston < info[1])
                                write(HIY"\n有您的信！请到风云城驿站来一趟．．\n\n"NOR);
                }
        write( HIR+"上次连线地址：" + ob->query("last_from") + "（"+
                           ctime(ob->query("last_on")) + "）\n\n" + NOR);
                write("请敲回车键［ＲＥＴＵＲＮ］．．．．．");
                input_to( "read_msg", user );
   }
}
// this is added for check wiz_ip 
private int valid_wiz_login(string id,string ip)
{
    string tmp, file;
        string *wiz_ips = ({});
        string tempip;
        int i;
        int sign=0;
        tmp=sprintf("/adm/etc/wizip/%s",id); 
    // read the list of the banned sites
    // 没有文件也可以进去
    if (file_size(tmp)>0)
    { 
        wiz_ips = explode(read_file(tmp), "\n"); 
        if(sizeof(wiz_ips)==0) return 3;
        for(i=0;i<sizeof(wiz_ips);i++)
        {
                if (regexp(ip, wiz_ips[i]) && wiz_ips[i]!="")
                {
                        sign=1;
                }
        }
        return sign;
    }
        return 1;
}
private void read_msg(string str, object user) {
        string startroom; 
        if( user->is_ghost() )
                startroom = DEATH_ROOM;
        else if( !stringp(startroom = user->query("startroom")) )
        {
                switch((string) user->query("national"))
                {
                case "汉族":
                        startroom = start_loc[0];
                        break;
                case "苗族":
                        startroom = start_loc[1];
                        break;
                case "满族":
                        startroom = start_loc[3];
                        break;
                case "蒙古族":
                        startroom = start_loc[2];
                        break;
                }
        user->set_temp("first_time_login", 1);
        } 
        if( !catch(load_object(startroom)) && user->move(startroom)){
                user->set("startroom", startroom);
        } else {
                user->move(START_ROOM);
                startroom = START_ROOM;
                user->set("startroom", START_ROOM);
        }
        tell_room(startroom, user->query("name") +
                          "连线进入这个世界。\n", ({user})); 
        CHANNEL_D->do_sys_channel("sys",

                          sprintf("%s(%s)由%s连线进入。", user->name(),user->query("id"),query_ip_name(user)) );
       // if(!wizardp(user)){
                UPDATE_D->check_user(user);
                STATUS_D->compare_status(user);
     //   }
        write(HIY "\n现在共有"+HIR+"/cmds/wiz/sameip"->tot_usr(user)+HIY+
                  "位玩家从你的站点（"+query_ip_name(user)+"）连线。\n\n"+NOR);
        user->set_temp("successful_login", 1);
        return;
} 
varargs void reconnect(object ob, object user, int silent)
{
        user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
        exec(user, ob);
        // retain the old encoding scheme on reconnects.
        //user->set_temp("char_encoding", ob->query_temp("char_encoding")); 
        user->reconnect();
        if( !silent )
        {
                tell_room(environment(user), user->query("name") +
                                  "重新连线回到这个世界。\n", ({user}));
        }
        CHANNEL_D->do_sys_channel(
                "sys",sprintf("%s(%s)由%s重新连线进入。", user->query("name"),
                                          user->query("id"), query_ip_name(user)) );
        UPDATE_D->check_user(user);
} 
int check_legal_id(string id)
{
        int i; 
        i = strlen(id); 
        if( (strlen(id) < 3) || (strlen(id) > 8 ) )
        {
                write("对不起，你的英文名字必须是 3 到 8 个英文字母。\n");
                return 0;
        }
        while(i--) if( id[i]<'a' || id[i]>'z' )
        {

                write("对不起，你的英文名字只能用英文字母。\n");
                return 0;
        }
        if( member_array(id, banned_id)!=-1 )
        {
                write("对不起，这种英文名字会造成其他人的困扰。\n");
                return 0;
        }
        return 1;
} 
string random_name()
{
        string *lname = ({
"赵","钱","孙","李","周","吴","郑","王","冯","陈","褚","卫","蒋","沈","韩","杨","朱","秦","尤","许","何","吕","施","张",
"孔","曹","严","华","金","魏","陶","姜","戚","谢","邹","喻","柏","水","窦","章","云","苏","潘","葛","奚","范","彭","郎",
"鲁","韦","昌","马","苗","凤","花","方","傻","任","袁","柳","邓","鲍","史","唐","费","廉","岑","薛","雷","贺","倪","汤",
"藤","殷","罗","华","郝","邬","安","常","乐","呆","时","付","皮","卞","齐","康","伍","余","元","卜","顾","盈","平","黄",
"和","穆","肖","尹","姚","邵","湛","汪","祁","毛","禹","狄","米","贝","明","藏","计","伏","成","戴","谈","宋","茅","庞",
"熊","纪","舒","屈","项","祝","董","梁","樊","胡","凌","霍","虞","万","支","柯","昝","管","卢","英","万","候","司马",
"上官","欧阳","夏候","诸葛","闻人","东方","赫连","皇甫","尉迟","公羊","澹台","公治",
"宗政","濮阳","淳于","单于","太叔","申屠","公孙","仲孙","辕轩","令狐","钟离","宇文",
"长孙","幕容","司徒","师空","颛孔","端木","巫马","公西","漆雕","乐正","壤驷","公良",
"拓趾","夹谷","宰父","谷梁","楚晋","阎法","汝鄢","涂钦","段千","百里","东郭","南郭",
"呼延","归海","羊舌","微生","岳","帅","缑","亢","况","后","有","琴","梁丘","左丘","东门","西门",
        });
        return (lname[random(200)] + chinese_number(random(20)));
} 
int check_legal_name(string name)
{
        int i;
        string tempname; 
        i = strlen(name); 
        if( (strlen(name) < 2) || (strlen(name) > 10 ) )
        {
                write("对不起，你的中文名字必须是一到五个中文字。\n");
                return 0;
        }
        while(i--)
        {

                if( name[i]<=' ' )
                {
                        write("对不起，你的中文名字不能用控制字元。\n");
                        return 0;
                }
                if( i%2==0 && !is_chinese(name[i..<0]) )
                {
                        write("对不起，请您用「中文」取名字。\n");
                        return 0;
                }
        }
        // changed by akuma
        // on 2002-10-09 
        foreach(tempname in banned_name)
        {
            if(strsrch(name,tempname)!=-1)
            {
                    write("对不起，这种名字会造成其他人的困扰。\n");
                    return 0;
            }
        }
        return 1;
} 
int check_legal_password(object ob,string pass)
{
        int i;
        int bigletter=0;
        int smlletter=0;
        int number=0;
        string id;
        i = strlen(pass);
        if( strlen(pass) <= 5)
        {
                write("对不起，你的密码必须最少六个字符。\n");
                return 0;
        }
        id= ob->query("id");
        if ( strsrch(id, pass) != -1 || strsrch(pass,id) != -1)
        {

        write("对不起，你的密码和你的英文名字太象了。\n");
                return 0;
        } 
        while(i--)
        {
                if( pass[i]<='Z' && pass[i] >='A' ) bigletter++;
                if( pass[i]<='z' && pass[i] >='a' ) smlletter++;
        }
        if( bigletter == 0 || smlletter == 0 ||
        bigletter+smlletter == strlen(pass))
        {
                write("您的密码必需包含大写" + HIR"和" + NOR"小写英文字母"
                          + HIR"和" + NOR"其它特殊符号（数字，标点）。\n");
        return 0;
        }
        return 1;
} 
object find_body(string name)
{
        object ob, *body; 
        if( objectp(ob = find_player(name)) )
                return ob;
        body = children(USER_OB);
        for(int i=0; i<sizeof(body); i++)
                if( clonep(body[i]) && getuid(body[i]) == name ) return body[i]; 
        return 0;
} 
int set_wizlock(int level)
{
        if( wiz_level(this_player(1)) <= level )
                return 0;
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        wiz_lock_level = level;
        return 1;
} 
int set_attribute(object user,int tol, int fle, int agi, int dur,
                                  int intt, int str, int con, int spi, int per,
                                  int cor, int cps, int kar)

{
        user->set("tol",tol);
        user->set("fle",fle);
        user->set("agi",agi);
        user->set("dur",dur);
        user->set("int",intt);
        user->set("str",str);
        user->set("con",con);
        user->set("spi",spi);
        user->set("per",per);
        user->set("cor",cor);
        user->set("cps",cps);
        user->set("kar",kar);
        return 1;
} 
int cphirdir(string dirstr, string newdirstr) {
        string *dir;
        int i;
        dir = get_dir(dirstr+"/");
        if(!mkdir(newdirstr)) write("FAILED\n");
        for(i=0; i<sizeof(dir); i++) {
                if(file_size(dirstr+"/"+dir[i]) == -2 )
                        cphirdir(dirstr +"/"+dir[i],newdirstr+"/"+dir[i]);
                cp(dirstr+"/"+dir[i], newdirstr+"/"+dir[i]);
        }
        return 1;
} 
int set_newuser_lock( int level) {
        new_user_lock = level;
        return level;
}    
