# 1 "C:\\Users\\rwillekes\\Documents\\Stack\\Documents\\Persoonlijk\\ITM2M\\arduino-music-player-demo\\pmf_player\\pmf_player.ino"
# 2 "C:\\Users\\rwillekes\\Documents\\Stack\\Documents\\Persoonlijk\\ITM2M\\arduino-music-player-demo\\pmf_player\\pmf_player.ino" 2
# 3 "C:\\Users\\rwillekes\\Documents\\Stack\\Documents\\Persoonlijk\\ITM2M\\arduino-music-player-demo\\pmf_player\\pmf_player.ino" 2

//============================================================================
// music data
//============================================================================
static const uint8_t 
# 7 "C:\\Users\\rwillekes\\Documents\\Stack\\Documents\\Persoonlijk\\ITM2M\\arduino-music-player-demo\\pmf_player\\pmf_player.ino" 3
                    __attribute__((__progmem__)) 
# 7 "C:\\Users\\rwillekes\\Documents\\Stack\\Documents\\Persoonlijk\\ITM2M\\arduino-music-player-demo\\pmf_player\\pmf_player.ino"
                            s_pmf_file[]=
{
# 10 "C:\\Users\\rwillekes\\Documents\\Stack\\Documents\\Persoonlijk\\ITM2M\\arduino-music-player-demo\\pmf_player\\pmf_player.ino" 2
};
//----------------------------------------------------------------------------


//============================================================================
// globals
//============================================================================
static pmf_player s_player;
static unsigned s_effect_channel=0;
//----------------------------------------------------------------------------


//============================================================================
// row_callback_test
//============================================================================
void row_callback_test(void *custom_data_, uint8_t channel_idx_, uint8_t &note_idx_, uint8_t &inst_idx_, uint8_t &volume_, uint8_t &effect_, uint8_t &effect_data_)
{
  if(channel_idx_==s_effect_channel)
  {
    static unsigned s_counter=1;
    if(--s_counter==0)
    {
      note_idx_=0+5*12; // C-5 (note+octave*12, note: 0=C, 1=C#, 2=D, 3=D#, 4=E, 5=F, 6=F#, 7=G, 8=G#, 9=A, 10=A#, 11=B)
      inst_idx_=2; // sample 2
      volume_=63; // volume 63 (max)
      s_counter=8; // hit note every 8th row
    }
  }
}
//----------------------------------------------------------------------------


//============================================================================
// example visualization (animate LED's for each track with music)
//============================================================================

enum {start_led_pin=8};
enum {max_channel_leds=6};




static void example_visualization(void *player_)
{
  const pmf_player *player=(const pmf_player*)player_;
  unsigned num_channels=((max_channel_leds)<(player->num_playback_channels())?(max_channel_leds):(player->num_playback_channels()));
  for(unsigned i=0; i<num_channels; ++i)
  {
    pmf_channel_info chl=player->channel_info(i);
    digitalWrite(start_led_pin+i, chl.note_hit?0x1:0x0);
  }
}
//----

void setup_example_visualization(pmf_player &player_)
{
  for(unsigned i=0; i<max_channel_leds; ++i)
  {
    pinMode(start_led_pin+i, 0x1);
    digitalWrite(start_led_pin+i, 0x0);
  }
  player_.set_tick_callback(&example_visualization, &player_);
}
//----------------------------------------------------------------------------


//============================================================================
// setup
//============================================================================
void setup()
{





  setup_disp();
  s_player.load(s_pmf_file);
/*

  // Uncomment this code block to enable basic LED visualization (make sure pins don't conflic with used audio device)

  setup_example_visualization(s_player);

*/
# 93 "C:\\Users\\rwillekes\\Documents\\Stack\\Documents\\Persoonlijk\\ITM2M\\arduino-music-player-demo\\pmf_player\\pmf_player.ino"
/*

  // Uncomment this code block to demo code-controlled effect. The code adds 13th channel to Aryx and plays drum beat every 8th row on the channel

  s_effect_channel=s_player.num_playback_channels();

  s_player.enable_playback_channels(s_player.num_playback_channels()+1); // add one extra audio channel for audio effects

  s_player.set_row_callback(&row_callback_test); // setup row callback for the effect

*/
# 100 "C:\\Users\\rwillekes\\Documents\\Stack\\Documents\\Persoonlijk\\ITM2M\\arduino-music-player-demo\\pmf_player\\pmf_player.ino"
  //s_player.start(22050);
}
//----------------------------------------------------------------------------


//============================================================================
// loop
//============================================================================
int main(void)
{
  while (1){
    s_player.update(); // keep updating the audio buffer...
    //set_disp();
  }
}
//----------------------------------------------------------------------------
