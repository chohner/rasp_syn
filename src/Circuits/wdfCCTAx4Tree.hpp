/*
 ==============================================================================

 This file is part of the RT-WDF library.
 Copyright (c) 2015,2016 - Maximilian Rest

 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3

 Details of these licenses can be found at: www.gnu.org/licenses

 RT-WDF is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 -----------------------------------------------------------------------------
 To release a closed-source product which uses RT-WDF, commercial licenses are
 available: write to rt-wdf@e-rm.de for more information.

 ==============================================================================

 wdfCCTAx4Tree.h
 auto-generated by MATLAB wdfLibrary version 0.0.2 on 08-Feb-2016 16:23:37
 for circuit Dempwolf_CCTA

 ==============================================================================
*/


#pragma once
#include "../rt-wdf_lib/Libs/rt-wdf/rt-wdf.h"

using namespace arma;

class wdfCCTAx4Tree: public wdfTree {

private:
    std::unique_ptr<wdfTerminatedResVSource> Vin;
    std::unique_ptr<wdfTerminatedResVSource> E;
    std::unique_ptr<wdfTerminatedCap> CI;
    std::unique_ptr<wdfTerminatedRes> RI;
    std::unique_ptr<wdfTerminatedRes> RG;
    std::unique_ptr<wdfTerminatedCap> CGK;
    std::unique_ptr<wdfTerminatedCap> CGP;
    std::unique_ptr<wdfTerminatedCap> CPK;
    std::unique_ptr<wdfTerminatedRes> RK;
    std::unique_ptr<wdfTerminatedCap> CK;
    std::unique_ptr<wdfTerminatedCap> CO;
    std::unique_ptr<wdfTerminatedRes> RO;
    std::unique_ptr<wdfTerminatedParallel> subtree4b;
    std::unique_ptr<wdfTerminatedParallel> tree5;
    std::unique_ptr<wdfTerminatedParallel> tree6;
    std::unique_ptr<wdfTerminatedSeries> subtree4a;
    std::unique_ptr<wdfTerminatedSeries> tree4;
    std::unique_ptr<wdfTerminatedSeries> subtree5a;
    std::string treeName = "Dempwolf CCTA - 176400 Hz";

public:
    wdfCCTAx4Tree() {

        setSamplerate(176400);

        paramData inputGain;
        inputGain.name = "Input Gain";
        inputGain.ID = 0;
        inputGain.type = doubleParam;
        inputGain.value = 0.1;
        inputGain.units = " ";
        inputGain.lowLim = 0;
        inputGain.highLim = 2;
        params.push_back(inputGain);

        Vin.reset( new wdfTerminatedResVSource(0,1) );
        E.reset( new wdfTerminatedResVSource(250,100000) );
        CI.reset( new wdfTerminatedCap(1.000000e-07,1) );
        RI.reset( new wdfTerminatedRes(1000000) );
        RG.reset( new wdfTerminatedRes(20000) );
        CGK.reset( new wdfTerminatedCap(1.600000e-12,1) );
        CGP.reset( new wdfTerminatedCap(1.700000e-12,1) );
        CPK.reset( new wdfTerminatedCap(4.600000e-13,1) );
        RK.reset( new wdfTerminatedRes(1500) );
        CK.reset( new wdfTerminatedCap(1.000000e-05,1) );
        CO.reset( new wdfTerminatedCap(1.000000e-08,1) );
        RO.reset( new wdfTerminatedRes(1000000) );
        subtree4a.reset( new wdfTerminatedSeries( CI.get(), Vin.get() ) );
        subtree4b.reset( new wdfTerminatedParallel( RI.get(), subtree4a.get() ) );
        tree4.reset( new wdfTerminatedSeries( RG.get(), subtree4b.get() ) );
        subtree5a.reset( new wdfTerminatedSeries( RO.get(), CO.get() ) );
        tree5.reset( new wdfTerminatedParallel( E.get(), subtree5a.get() ) );
        tree6.reset( new wdfTerminatedParallel( CK.get(), RK.get()) );

        subtreeCount = 6;
        subtreeEntryNodes = new wdfTreeNode*[subtreeCount];
        subtreeEntryNodes[0] = CGP.get();
        subtreeEntryNodes[1] = CGK.get();
        subtreeEntryNodes[2] = CPK.get();
        subtreeEntryNodes[3] = tree4.get();
        subtreeEntryNodes[4] = tree5.get();
        subtreeEntryNodes[5] = tree6.get();

        root.reset( new wdfRootNL(subtreeCount, {TRI_DW}, 1) );
        Rp = new double[subtreeCount] ();
    }

    ~wdfCCTAx4Tree() {
        Vin.reset();
        E.reset();
        CI.reset();
        RI.reset();
        RG.reset();
        CGK.reset();
        CGP.reset();
        CPK.reset();
        RK.reset();
        CK.reset();
        CO.reset();
        RO.reset();
        subtree4a.reset();
        subtree4b.reset();
        tree4.reset();
        subtree5a.reset();
        tree5.reset();
        tree6.reset();

        delete subtreeEntryNodes;
        root.reset();
        delete Rp;
    }

    int setRootMatrData(matData* rootMats, double* Rp) {

        //------------------------- S matrix -------------------------
        rootMats->Smat.at(0,0) =  9.7675066852639857994944e-01;
        rootMats->Smat.at(0,1) =  1.1282414515950730648369e-03;
        rootMats->Smat.at(0,2) =  1.1848993068623841357079e-03;
        rootMats->Smat.at(0,3) =  6.3686973459653046969096e-07;
        rootMats->Smat.at(0,4) =  3.2080291249381219596121e-04;
        rootMats->Smat.at(0,5) =  5.6020985532373939559322e-05;
        rootMats->Smat.at(0,6) =  2.1743629254245045584470e-02;
        rootMats->Smat.at(0,7) = -2.1799650239777430826837e-02;
        rootMats->Smat.at(1,0) =  1.1282414515950730648369e-03;
        rootMats->Smat.at(1,1) =  9.0278676527539203355843e-01;
        rootMats->Smat.at(1,2) = -1.1405387162485602133705e-03;
        rootMats->Smat.at(1,3) =  1.0740850732626537698128e-03;
        rootMats->Smat.at(1,4) =  1.8310004869643007283729e-07;
        rootMats->Smat.at(1,5) =  9.4998610934251562221142e-02;
        rootMats->Smat.at(1,6) =  1.2114164604955630111000e-05;
        rootMats->Smat.at(1,7) = -9.5010725098856524395430e-02;
        rootMats->Smat.at(2,0) =  1.9756224270748032889600e+00;
        rootMats->Smat.at(2,1) = -1.9016585238237968535913e+00;
        rootMats->Smat.at(2,2) = -9.9767456197688919594668e-01;
        rootMats->Smat.at(2,3) = -1.0734482035280575387692e-03;
        rootMats->Smat.at(2,4) =  3.2061981244511570093153e-04;
        rootMats->Smat.at(2,5) = -9.4942589948719180448222e-02;
        rootMats->Smat.at(2,6) =  2.1731515089640090349077e-02;
        rootMats->Smat.at(2,7) =  7.3211074859079072751911e-02;
        rootMats->Smat.at(3,0) =  1.1282414515953274186666e-03;
        rootMats->Smat.at(3,1) =  1.9027867652753924776476e+00;
        rootMats->Smat.at(3,2) = -1.1405387162485608638918e-03;
        rootMats->Smat.at(3,3) = -9.9892591492673732389562e-01;
        rootMats->Smat.at(3,4) =  1.8310004869643012577685e-07;
        rootMats->Smat.at(3,5) =  9.4998610934251589976718e-02;
        rootMats->Smat.at(3,6) =  1.2114164604955628416934e-05;
        rootMats->Smat.at(3,7) = -9.5010725098856524395430e-02;
        rootMats->Smat.at(4,0) =  1.9767506685263991350610e+00;
        rootMats->Smat.at(4,1) =  1.1282414515948813778928e-03;
        rootMats->Smat.at(4,2) =  1.1848993068623843525483e-03;
        rootMats->Smat.at(4,3) =  6.3686973459627890090562e-07;
        rootMats->Smat.at(4,4) = -9.9967919708750652141305e-01;
        rootMats->Smat.at(4,5) =  5.6020985532390771798050e-05;
        rootMats->Smat.at(4,6) =  2.1743629254245045584470e-02;
        rootMats->Smat.at(4,7) = -2.1799650239777465521307e-02;
        rootMats->Smat.at(5,0) =  1.1220635798095278303638e-03;
        rootMats->Smat.at(5,1) =  1.9027598398856986339212e+00;
        rootMats->Smat.at(5,2) = -1.1405262727172198970044e-03;
        rootMats->Smat.at(5,3) =  1.0740698744186793697764e-03;
        rootMats->Smat.at(5,4) =  1.8209745424018333748918e-07;
        rootMats->Smat.at(5,5) = -9.0497443603367933029347e-01;
        rootMats->Smat.at(5,6) =  1.8280595453390446891717e-05;
        rootMats->Smat.at(5,7) =  1.9049561554382261618912e+00;
        rootMats->Smat.at(6,0) =  1.9767444906546132177283e+00;
        rootMats->Smat.at(6,1) =  1.1013160619013969560021e-03;
        rootMats->Smat.at(6,2) =  1.1849117503937248857548e-03;
        rootMats->Smat.at(6,3) =  6.2167089062210046947313e-07;
        rootMats->Smat.at(6,4) =  3.2080190989935584641723e-04;
        rootMats->Smat.at(6,5) =  8.2974017601344815476747e-05;
        rootMats->Smat.at(6,6) = -9.7825020431490639083449e-01;
        rootMats->Smat.at(6,7) =  1.9781672302973056787323e+00;
        rootMats->Smat.at(7,0) = -6.1778717853138369304295e-06;
        rootMats->Smat.at(7,1) = -2.6925389693611327755068e-05;
        rootMats->Smat.at(7,2) =  1.2443531340680499273585e-08;
        rootMats->Smat.at(7,3) = -1.5198843974249724475128e-08;
        rootMats->Smat.at(7,4) = -1.0025944562950133309730e-09;
        rootMats->Smat.at(7,5) =  2.6953032068938214326978e-05;
        rootMats->Smat.at(7,6) =  6.1664308484294516740296e-06;
        rootMats->Smat.at(7,7) =  9.9996688053708260301988e-01;

        //------------------------- E matrix -------------------------
        rootMats->Emat.at(0,0) =  5.0423929676195126947658e-02;
        rootMats->Emat.at(0,1) =  5.6388352946144771563747e-04;
        rootMats->Emat.at(0,2) =  1.3806238662396493749318e-02;
        rootMats->Emat.at(0,3) =  4.9860046146296875535509e-02;
        rootMats->Emat.at(0,4) =  9.3576983166140070835581e-01;
        rootMats->Emat.at(0,5) = -9.8562987780769806267500e-01;
        rootMats->Emat.at(1,0) = -1.1147127772318164012910e-02;
        rootMats->Emat.at(1,1) =  1.1055297903407954734911e-02;
        rootMats->Emat.at(1,2) =  1.6211651472016407830173e-04;
        rootMats->Emat.at(1,3) =  9.7779757431557456914817e-01;
        rootMats->Emat.at(1,4) =  1.0985011257599607698010e-02;
        rootMats->Emat.at(1,5) = -9.8878258557317444399359e-01;

        //------------------------- F matrix -------------------------
        rootMats->Fmat.at(0,0) = -8.5072455525956902420148e+04;
        rootMats->Fmat.at(0,1) = -9.9894332741893651927967e+02;
        rootMats->Fmat.at(1,0) = -9.9894332741893651927967e+02;
        rootMats->Fmat.at(1,1) = -1.9584924006887667928822e+04;

        //------------------------- M matrix -------------------------
        rootMats->Mmat.at(0,0) = -8.7685788510297357767342e-01;
        rootMats->Mmat.at(0,1) = -2.0982828747893013388026e-02;
        rootMats->Mmat.at(0,2) =  2.7288244295352658691511e-02;
        rootMats->Mmat.at(0,3) = -1.8558750563385553178364e+00;
        rootMats->Mmat.at(0,4) =  1.8495696408076018890654e+00;
        rootMats->Mmat.at(0,5) =  6.3054155309525405925797e-03;
        rootMats->Mmat.at(1,0) = -2.2294255544636324556373e-02;
        rootMats->Mmat.at(1,1) = -9.7788940419318404195792e-01;
        rootMats->Mmat.at(1,2) =  3.2423302944033168026053e-04;
        rootMats->Mmat.at(1,3) =  1.9555951486311498044302e+00;
        rootMats->Mmat.at(1,4) =  2.1970022515199454787860e-02;
        rootMats->Mmat.at(1,5) = -1.9775651711463497761656e+00;
        rootMats->Mmat.at(2,0) =  1.0084785935239029552868e-01;
        rootMats->Mmat.at(2,1) =  1.1277670589228934797110e-03;
        rootMats->Mmat.at(2,2) = -9.7238752267520733862938e-01;
        rootMats->Mmat.at(2,3) =  9.9720092292593612293139e-02;
        rootMats->Mmat.at(2,4) =  1.8715396633228020828454e+00;
        rootMats->Mmat.at(2,5) = -1.9712597556153965694392e+00;
        rootMats->Mmat.at(3,0) = -2.2294254472918217935273e-02;
        rootMats->Mmat.at(3,1) =  2.2110279456167565570457e-02;
        rootMats->Mmat.at(3,2) =  3.2414236862324041299824e-04;
        rootMats->Mmat.at(3,3) =  9.5559546605351619597002e-01;
        rootMats->Mmat.at(3,4) =  2.1970112104297966071353e-02;
        rootMats->Mmat.at(3,5) =  2.2434421842185692241856e-02;
        rootMats->Mmat.at(4,0) =  1.0084786042410838480254e-01;
        rootMats->Mmat.at(4,1) =  1.1274507082745452435368e-03;
        rootMats->Mmat.at(4,2) =  2.7612386663975908157598e-02;
        rootMats->Mmat.at(4,3) =  9.9720409714960447922216e-02;
        rootMats->Mmat.at(4,4) =  8.7153975291190044494272e-01;
        rootMats->Mmat.at(4,5) =  2.8739837373138676923645e-02;
        rootMats->Mmat.at(5,0) =  1.0717181236096842548849e-09;
        rootMats->Mmat.at(5,1) = -3.1635064834933631116971e-07;
        rootMats->Mmat.at(5,2) = -9.0660817084633842878563e-08;
        rootMats->Mmat.at(5,3) =  3.1742236672183189488856e-07;
        rootMats->Mmat.at(5,4) =  8.9589098961029189536164e-08;
        rootMats->Mmat.at(5,5) =  9.9999959298853424716214e-01;

        //------------------------- N matrix -------------------------
        rootMats->Nmat.at(0,0) = -1.6814702439707590383478e+05;
        rootMats->Nmat.at(0,1) =  3.7171961358937456679996e+04;
        rootMats->Nmat.at(1,0) = -1.9978866548378953211795e+03;
        rootMats->Nmat.at(1,1) = -3.9169848013775350409560e+04;
        rootMats->Nmat.at(2,0) = -1.7014491105191386304796e+05;
        rootMats->Nmat.at(2,1) = -1.9978866548378698553279e+03;
        rootMats->Nmat.at(3,0) = -1.9973280133049941014178e+03;
        rootMats->Nmat.at(3,1) = -3.9169287585330843285192e+04;
        rootMats->Nmat.at(4,0) = -1.7014435241038093226962e+05;
        rootMats->Nmat.at(4,1) = -1.9973262263933752365119e+03;
        rootMats->Nmat.at(5,0) =  5.5864153285907680590583e-01;
        rootMats->Nmat.at(5,1) =  5.6042844449641460169431e-01;

        return 0;
    }

    void setInputValue(double signalIn) {
        Vin->Vs = params[0].value * signalIn;
    }

    double getOutputValue() {
        return RO->upPort->getPortVoltage();
    }

    const char* getTreeIdentifier() {
        return treeName.c_str();
    }

    void setParam(size_t paramID, double paramValue) {
        if (paramID == 0) {
            params[0].value = paramValue;
        }
    }
};
