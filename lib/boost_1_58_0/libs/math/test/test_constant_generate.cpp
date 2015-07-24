// Copyright John Maddock 2010.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef _MSC_VER
#  pragma warning (disable : 4127) // conditional expression is constant.
#  pragma warning (disable : 4512) // assignment operator could not be generated.
#  pragma warning (disable : 4100) // assignment operator could not be generated.
#  pragma warning (disable : 4996) //To disable this warning, use -D_SCL_SECURE_NO_WARNINGS.
#endif

// To add new constants, add a function that calculates the value of the constant to
// boost/math/constants/calculate_constants.hpp

#include <boost/math/constants/generate.hpp>
#include <boost/math/constants/calculate_constants.hpp>

int main()
{
  // Rational fractions.
   BOOST_CONSTANTS_GENERATE(half);
   BOOST_CONSTANTS_GENERATE(third);
   BOOST_CONSTANTS_GENERATE(twothirds);
   BOOST_CONSTANTS_GENERATE(two_thirds);
   BOOST_CONSTANTS_GENERATE(three_quarters);
   // two and related.
   BOOST_CONSTANTS_GENERATE(root_two);
   BOOST_CONSTANTS_GENERATE(root_three);
   BOOST_CONSTANTS_GENERATE(half_root_two);
   BOOST_CONSTANTS_GENERATE(ln_two);
   BOOST_CONSTANTS_GENERATE(ln_ten);
   BOOST_CONSTANTS_GENERATE(ln_ln_two);
   BOOST_CONSTANTS_GENERATE(root_ln_four);
   BOOST_CONSTANTS_GENERATE(one_div_root_two);
   // pi and related.
   BOOST_CONSTANTS_GENERATE(pi);
   BOOST_CONSTANTS_GENERATE(half_pi);
   BOOST_CONSTANTS_GENERATE(third_pi);
   BOOST_CONSTANTS_GENERATE(sixth_pi);
   BOOST_CONSTANTS_GENERATE(two_pi);
   BOOST_CONSTANTS_GENERATE(two_thirds_pi);
   BOOST_CONSTANTS_GENERATE(three_quarters_pi);
   BOOST_CONSTANTS_GENERATE(four_thirds_pi);
   BOOST_CONSTANTS_GENERATE(one_div_two_pi);
   BOOST_CONSTANTS_GENERATE(one_div_root_two_pi);
   BOOST_CONSTANTS_GENERATE(root_pi);
   BOOST_CONSTANTS_GENERATE(root_half_pi);
   BOOST_CONSTANTS_GENERATE(root_two_pi);
   BOOST_CONSTANTS_GENERATE(log_root_two_pi);
   BOOST_CONSTANTS_GENERATE(two_div_pi);
   BOOST_CONSTANTS_GENERATE(root_two_div_pi);

   BOOST_CONSTANTS_GENERATE(one_div_root_pi);
   BOOST_CONSTANTS_GENERATE(root_one_div_pi);
   BOOST_CONSTANTS_GENERATE(pi_minus_three);
   BOOST_CONSTANTS_GENERATE(four_minus_pi);
   //BOOST_CONSTANTS_GENERATE(pow23_four_minus_pi);

   BOOST_CONSTANTS_GENERATE(pi_pow_e);
   BOOST_CONSTANTS_GENERATE(pi_sqr);
   BOOST_CONSTANTS_GENERATE(pi_sqr_div_six);
   BOOST_CONSTANTS_GENERATE(pi_cubed);
   BOOST_CONSTANTS_GENERATE(cbrt_pi);
   BOOST_CONSTANTS_GENERATE(one_div_cbrt_pi);

   // Euler's e and related.
   BOOST_CONSTANTS_GENERATE(e);
   BOOST_CONSTANTS_GENERATE(exp_minus_half);

   BOOST_CONSTANTS_GENERATE(e_pow_pi);
   BOOST_CONSTANTS_GENERATE(root_e);
   BOOST_CONSTANTS_GENERATE(log10_e);
   BOOST_CONSTANTS_GENERATE(one_div_log10_e);

   // Trigonometric
   BOOST_CONSTANTS_GENERATE(degree);
   BOOST_CONSTANTS_GENERATE(radian);
   BOOST_CONSTANTS_GENERATE(sin_one);
   BOOST_CONSTANTS_GENERATE(cos_one);
   BOOST_CONSTANTS_GENERATE(sinh_one);
   BOOST_CONSTANTS_GENERATE(cosh_one);

   // Phi
   BOOST_CONSTANTS_GENERATE(phi);
   BOOST_CONSTANTS_GENERATE(ln_phi);
   BOOST_CONSTANTS_GENERATE(one_div_ln_phi);
   
// Euler's Gamma constant http://en.wikipedia.org/wiki/Euler%E2%80%93Mascheroni_constant
   // gamma name deprecated - see euler above

      BOOST_CONSTANTS_GENERATE(euler);
      BOOST_CONSTANTS_GENERATE(one_div_euler);
      BOOST_CONSTANTS_GENERATE(euler_sqr);
 //  BOOST_CONSTANTS_GENERATE(gamma);
 //  BOOST_CONSTANTS_GENERATE(one_div_gamma);
 //  BOOST_CONSTANTS_GENERATE(gamma_sqr);

// zeta
   BOOST_CONSTANTS_GENERATE(zeta_two);
   BOOST_CONSTANTS_GENERATE(zeta_three);
   BOOST_CONSTANTS_GENERATE(catalan);
   BOOST_CONSTANTS_GENERATE(glaisher);
   BOOST_CONSTANTS_GENERATE(khinchin);
   BOOST_CONSTANTS_GENERATE(extreme_value_skewness);
   BOOST_CONSTANTS_GENERATE(rayleigh_skewness);
   BOOST_CONSTANTS_GENERATE(rayleigh_kurtosis);
   BOOST_CONSTANTS_GENERATE(rayleigh_kurtosis_excess);
   
   return 0;
}

/*

Output
------ Build started: Project: test_constant_generate, Configuration: Release Win32 ------
  test_constant_generate.vcxproj -> J:\Cpp\MathToolkit\test\Math_test\Release\test_constant_generate.exe
  BOOST_DEFINE_MATH_CONSTANT(half, 0.5e0, "0.5e0");
  BOOST_DEFINE_MATH_CONSTANT(third, 0.333333333333333333333333333333333333e0, "0.333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333e0");
  BOOST_DEFINE_MATH_CONSTANT(twothirds, 0.666666666666666666666666666666666666e0, "0.666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666667e0");
  BOOST_DEFINE_MATH_CONSTANT(two_thirds, 0.666666666666666666666666666666666666e0, "0.666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666667e0");
  BOOST_DEFINE_MATH_CONSTANT(three_quarters, 0.75e0, "0.75e0");
  BOOST_DEFINE_MATH_CONSTANT(root_two, 1.414213562373095048801688724209698078e0, "1.41421356237309504880168872420969807856967187537694807317667973799073247846210703885038753432764157274e0");
  BOOST_DEFINE_MATH_CONSTANT(root_three, 1.732050807568877293527446341505872366e0, "1.73205080756887729352744634150587236694280525381038062805580697945193301690880003708114618675724857568e0");
  BOOST_DEFINE_MATH_CONSTANT(half_root_two, 0.707106781186547524400844362104849039e0, "0.707106781186547524400844362104849039284835937688474036588339868995366239231053519425193767163820786368e0");
  BOOST_DEFINE_MATH_CONSTANT(ln_two, 0.693147180559945309417232121458176568e0, "0.693147180559945309417232121458176568075500134360255254120680009493393621969694715605863326996418687542e0");
  BOOST_DEFINE_MATH_CONSTANT(ln_ln_two, -0.366512920581664327012439158232669469e0, "-0.366512920581664327012439158232669469454263447837105263053677713670561615319352738549455822856698908358e0");
  BOOST_DEFINE_MATH_CONSTANT(root_ln_four, 1.177410022515474691011569326459699637e0, "1.17741002251547469101156932645969963774738568938582053852252575650002658854698492680841813836877081107e0");
  BOOST_DEFINE_MATH_CONSTANT(one_div_root_two, 0.707106781186547524400844362104849039e0, "0.707106781186547524400844362104849039284835937688474036588339868995366239231053519425193767163820786368e0");
  BOOST_DEFINE_MATH_CONSTANT(pi, 3.141592653589793238462643383279502884e0, "3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798e0");
  BOOST_DEFINE_MATH_CONSTANT(half_pi, 1.570796326794896619231321691639751442e0, "1.57079632679489661923132169163975144209858469968755291048747229615390820314310449931401741267105853399e0");
  BOOST_DEFINE_MATH_CONSTANT(third_pi, 1.047197551196597746154214461093167628e0, "1.04719755119659774615421446109316762806572313312503527365831486410260546876206966620934494178070568933e0");
  BOOST_DEFINE_MATH_CONSTANT(sixth_pi, 0.523598775598298873077107230546583814e0, "0.523598775598298873077107230546583814032861566562517636829157432051302734381034833104672470890352844664e0");
  BOOST_DEFINE_MATH_CONSTANT(two_pi, 6.283185307179586476925286766559005768e0, "6.28318530717958647692528676655900576839433879875021164194988918461563281257241799725606965068423413596e0");
  BOOST_DEFINE_MATH_CONSTANT(two_thirds_pi, 2.094395102393195492308428922186335256e0, "2.09439510239319549230842892218633525613144626625007054731662972820521093752413933241868988356141137865e0");
  BOOST_DEFINE_MATH_CONSTANT(three_quarters_pi, 2.356194490192344928846982537459627163e0, "2.35619449019234492884698253745962716314787704953132936573120844423086230471465674897102611900658780099e0");
  BOOST_DEFINE_MATH_CONSTANT(four_thirds_pi, 4.188790204786390984616857844372670512e0, "4.18879020478639098461685784437267051226289253250014109463325945641042187504827866483737976712282275731e0");
  BOOST_DEFINE_MATH_CONSTANT(one_div_two_pi, 0.159154943091895335768883763372514362e0, "0.159154943091895335768883763372514362034459645740456448747667344058896797634226535090113802766253085956e0");
  BOOST_DEFINE_MATH_CONSTANT(one_div_root_two_pi, 0.398942280401432677939946059934381868e0, "0.39894228040143267793994605993438186847585863116493465766592582967065792589930183850125233390730693643e0");
  BOOST_DEFINE_MATH_CONSTANT(root_pi, 1.772453850905516027298167483341145182e0, "1.77245385090551602729816748334114518279754945612238712821380778985291128459103218137495065673854466542e0");
  BOOST_DEFINE_MATH_CONSTANT(root_half_pi, 1.253314137315500251207882642405522626e0, "1.25331413731550025120788264240552262650349337030496915831496178817114682730392098747329791918902863306e0");
  BOOST_DEFINE_MATH_CONSTANT(root_two_pi, 2.506628274631000502415765284811045253e0, "2.50662827463100050241576528481104525300698674060993831662992357634229365460784197494659583837805726612e0");
  BOOST_DEFINE_MATH_CONSTANT(two_div_pi, 0.636619772367581343075535053490057448e0, "0.636619772367581343075535053490057448137838582961825794990669376235587190536906140360455211065012343824e0");
  BOOST_DEFINE_MATH_CONSTANT(root_two_div_pi, 0.797884560802865355879892119868763736e0, "0.797884560802865355879892119868763736951717262329869315331851659341315851798603677002504667814613872861e0");
  BOOST_DEFINE_MATH_CONSTANT(one_div_root_pi, 0.564189583547756286948079451560772585e0, "0.564189583547756286948079451560772585844050629328998856844085721710642468441493414486743660202107363443e0");
  BOOST_DEFINE_MATH_CONSTANT(root_one_div_pi, 0.564189583547756286948079451560772585e0, "0.564189583547756286948079451560772585844050629328998856844085721710642468441493414486743660202107363443e0");
  BOOST_DEFINE_MATH_CONSTANT(pi_minus_three, 0.141592653589793238462643383279502884e0, "0.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982e0");
  BOOST_DEFINE_MATH_CONSTANT(four_minus_pi, 0.858407346410206761537356616720497115e0, "0.858407346410206761537356616720497115802830600624894179025055407692183593713791001371965174657882932018e0");
  BOOST_DEFINE_MATH_CONSTANT(pow23_four_minus_pi, 0.795316767371597544348395335056806580e0, "0.795316767371597544348395335056806580727639173327713205445302234388856268267518187590758006888600828437e0");
  BOOST_DEFINE_MATH_CONSTANT(pi_pow_e, 22.459157718361045473427152204543735027e0, "22.4591577183610454734271522045437350275893151339966922492030025540669260403991179123185197527271430315e0");
  BOOST_DEFINE_MATH_CONSTANT(pi_sqr, 9.869604401089358618834490999876151135e0, "9.86960440108935861883449099987615113531369940724079062641334937622004482241920524300177340371855223182e0");
  BOOST_DEFINE_MATH_CONSTANT(pi_sqr_div_six, 1.644934066848226436472415166646025189e0, "1.6449340668482264364724151666460251892189499012067984377355582293700074704032008738336289006197587053e0");
  BOOST_DEFINE_MATH_CONSTANT(pi_cubed, 31.006276680299820175476315067101395202e0, "31.006276680299820175476315067101395202225288565885107694144538103806394917465706037566701032602886193e0");
  BOOST_DEFINE_MATH_CONSTANT(cbrt_pi, 1.464591887561523263020142527263790391e0, "1.4645918875615232630201425272637903917385968556279371743572559371383936497982862661456820678203538209e0");
  BOOST_DEFINE_MATH_CONSTANT(one_div_cbrt_pi, 0.682784063255295681467020833158164598e0, "0.682784063255295681467020833158164598108367515632448804042681583118899226433403918237673501922595519866e0");
  BOOST_DEFINE_MATH_CONSTANT(e, 2.718281828459045235360287471352662497e0, "2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642743e0");
  BOOST_DEFINE_MATH_CONSTANT(exp_minus_half, 0.606530659712633423603799534991180453e0, "0.606530659712633423603799534991180453441918135487186955682892158735056519413748423998647611507989456026e0");
  BOOST_DEFINE_MATH_CONSTANT(e_pow_pi, 23.140692632779269005729086367948547380e0, "23.1406926327792690057290863679485473802661062426002119934450464095243423506904527835169719970675492197e0");
  BOOST_DEFINE_MATH_CONSTANT(root_e, 1.648721270700128146848650787814163571e0, "1.648721270700128146848650787814163571653776100710148011575079311640661021194215608632776520056366643e0");
  BOOST_DEFINE_MATH_CONSTANT(log10_e, 0.434294481903251827651128918916605082e0, "0.434294481903251827651128918916605082294397005803666566114453783165864649208870774729224949338431748319e0");
  BOOST_DEFINE_MATH_CONSTANT(one_div_log10_e, 2.302585092994045684017991454684364207e0, "2.30258509299404568401799145468436420760110148862877297603332790096757260967735248023599720508959829834e0");
  BOOST_DEFINE_MATH_CONSTANT(degree, 0.017453292519943295769236907684886127e0, "0.0174532925199432957692369076848861271344287188854172545609719144017100911460344944368224156963450948221e0");
  BOOST_DEFINE_MATH_CONSTANT(radian, 57.295779513082320876798154814105170332e0, "57.2957795130823208767981548141051703324054724665643215491602438612028471483215526324409689958511109442e0");
  BOOST_DEFINE_MATH_CONSTANT(sin_one, 0.841470984807896506652502321630298999e0, "0.841470984807896506652502321630298999622563060798371065672751709991910404391239668948639743543052695854e0");
  BOOST_DEFINE_MATH_CONSTANT(cos_one, 0.540302305868139717400936607442976603e0, "0.540302305868139717400936607442976603732310420617922227670097255381100394774471764517951856087183089344e0");
  BOOST_DEFINE_MATH_CONSTANT(sinh_one, 1.175201193643801456882381850595600815e0, "1.17520119364380145688238185059560081515571798133409587022956541301330756730432389560711745208962339184e0");
  BOOST_DEFINE_MATH_CONSTANT(cosh_one, 1.543080634815243778477905620757061682e0, "1.54308063481524377847790562075706168260152911236586370473740221471076906304922369896426472643554303559e0");
  BOOST_DEFINE_MATH_CONSTANT(phi, 1.618033988749894848204586834365638117e0, "1.61803398874989484820458683436563811772030917980576286213544862270526046281890244970720720418939113748e0");
  BOOST_DEFINE_MATH_CONSTANT(ln_phi, 0.481211825059603447497758913424368423e0, "0.481211825059603447497758913424368423135184334385660519661018168840163867608221774412009429122723474997e0");
  BOOST_DEFINE_MATH_CONSTANT(one_div_ln_phi, 2.078086921235027537601322606117795767e0, "2.07808692123502753760132260611779576774219226778328348027813992191974386928553540901445615414453604822e0");
  BOOST_DEFINE_MATH_CONSTANT(euler, 0.577215664901532860606512090082402431e0, "0.577215664901532860606512090082402431042159335939923598805767234884867726777664670936947063291746749515e0");
  BOOST_DEFINE_MATH_CONSTANT(one_div_euler, 1.732454714600633473583025315860829681e0, "1.73245471460063347358302531586082968115577655226680502204843613287065531408655243008832840219409928068e0");
  BOOST_DEFINE_MATH_CONSTANT(euler_sqr, 0.333177923807718674318376136355244226e0, "0.333177923807718674318376136355244226659417140249629743150833338002265793695756669661263268631715977303e0");
  BOOST_DEFINE_MATH_CONSTANT(zeta_two, 1.644934066848226436472415166646025189e0, "1.6449340668482264364724151666460251892189499012067984377355582293700074704032008738336289006197587053e0");
  BOOST_DEFINE_MATH_CONSTANT(zeta_three, 1.202056903159594285399738161511449990e0, "1.20205690315959428539973816151144999076498629234049888179227155534183820578631309018645587360933525815e0");
  BOOST_DEFINE_MATH_CONSTANT(catalan, 0.915965594177219015054603514932384110e0, "0.915965594177219015054603514932384110774149374281672134266498119621763019776254769479356512926115106249e0");
  BOOST_DEFINE_MATH_CONSTANT(glaisher, 1.282427129100622636875342568869791727e0, "1.28242712910062263687534256886979172776768892732500119206374002174040630885882646112973649195820237439e0");
  BOOST_DEFINE_MATH_CONSTANT(khinchin, 2.685452001065306445309714835481795693e0, "2.685452001065306445309714835481795693820382293994462953051152345557218859537152002801141174931847698e0");
  BOOST_DEFINE_MATH_CONSTANT(extreme_value_skewness, 1.139547099404648657492793019389846112e0, "1.13954709940464865749279301938984611208759979583655182472165571008524800770607068570718754688693851502e0");
  BOOST_DEFINE_MATH_CONSTANT(rayleigh_skewness, 0.631110657818937138191899351544227779e0, "0.631110657818937138191899351544227779844042203134719497658094585692926819617473725459905027032537306794e0");
  BOOST_DEFINE_MATH_CONSTANT(rayleigh_kurtosis, 3.245089300687638062848660410619754415e0, "3.24508930068763806284866041061975441541706673178920936177133764493367904540874159051490619368679348977e0");
  BOOST_DEFINE_MATH_CONSTANT(rayleigh_kurtosis_excess, 0.245089300687638062848660410619754415e0, "0.245089300687638062848660410619754415417066731789209361771337644933679045408741590514906193686793489774e0");
========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========


*/

