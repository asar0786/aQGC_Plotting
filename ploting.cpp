
void ploting()
{
TFile *f1 = new TFile("pureSM50k.root");
TFile *f2 = new TFile("aQGC_SM50k.root");
TFile *f3 = new TFile("aQGC_reweight50k_LHEWeight.root");
TFile *f4 = new TFile("aQGC2018_50k_DS.root");
TTree *t1 =(TTree*)f1->Get("tree");
TTree *t2 =(TTree*)f2->Get("tree");
TTree *t3 =(TTree*)f3->Get("tree");
TTree *t4 =(TTree*)f4->Get("tree");
TCanvas *c1 =new TCanvas("c1","title",600,600);
c1->SetLogy();
Float_t Wqrk0_pt = 0;
Double_t LHEWeight[1164] = {};
t1->SetBranchAddress("Wqrk0_pt",&Wqrk0_pt);
t2->SetBranchAddress("Wqrk0_pt",&Wqrk0_pt);
t3->SetBranchAddress("Wqrk0_pt",&Wqrk0_pt);
t4->SetBranchAddress("Wqrk0_pt",&Wqrk0_pt);
t3->SetBranchAddress("LHEWeight",&LHEWeight);
t4->SetBranchAddress("LHEWeight",&LHEWeight);
//t2->SetBranchAddress("LHEWeight",&LHEWeight);
TH1F *h1 = new TH1F("h1","Test",15,0,1000);
TH1F *h2 = new TH1F("h2","SM_aQGC_Com.",15,0,1000);
TH1F *h3 = new TH1F("h3","Test",15,0,1000);
TH1F *h4 = new TH1F("h4","Test",15,0,1000);
gStyle->SetOptStat(0);
Int_t nentries1 = (Int_t)t1->GetEntries();
for (Int_t i=0; i< nentries1; i++)
	{
		t2->GetEntry(i);
		//h2->Fill(Wqrk0_pt);
		h1->Fill(Wqrk0_pt,140.0*251.0);
	}
Int_t nentries2 = (Int_t)t2->GetEntries();
for (Int_t i=0; i< nentries2; i++)
	{
		t2->GetEntry(i);
		//h2->Fill(Wqrk0_pt);
		h2->Fill(Wqrk0_pt,140.0*247.49);
	}
Int_t nentries3 = (Int_t)t3->GetEntries();
for (Int_t i=0; i< nentries3; i++)
	{
		t3->GetEntry(i);
		if (i <5){
		std::cout<<"LHEWeight: "<<LHEWeight[0]<<" :"<<LHEWeight[146]<<" : "<<LHEWeight[147]<<std::endl;
		}	
//		h1->Fill(Wqrk0_pt);
		h3->Fill(Wqrk0_pt,(140*4927*(LHEWeight[147]/LHEWeight[0])));
	}
Int_t nentries4 = (Int_t)t4->GetEntries();
for (Int_t i=0; i< nentries4; i++)
	{
		t4->GetEntry(i);
		if (i <5){
		std::cout<<"LHEWeight: "<<LHEWeight[0]<<" :"<<LHEWeight[146]<<" : "<<LHEWeight[147]<<std::endl;
		}	
	//	h1->Fill(Wqrk0_pt);
		h4->Fill(Wqrk0_pt,(140*3190.14*(LHEWeight[147]/LHEWeight[0])));
	}
double norm1 = h1->GetEntries();
double norm2 = h2->GetEntries();
double norm3 = h3->GetEntries();
double norm4 = h4->GetEntries();
h1->Scale(1/(norm1));
h2->Scale(1/norm2);
h3->Scale(1/norm3);
h4->Scale(1/norm4);
//h2->Scale(140*0.9*LHEWeight[155]/(LHEWeight[0]*h2->Integral()));
h1->GetYaxis()->SetRange(10,100000);
h1->SetMarkerStyle(22); h1->SetMarkerSize(2); h1->SetMarkerColor(3);
h2->GetXaxis()->SetTitle("Wqrk0_pt");
h2->GetYaxis()->SetTitle("nEvents");
h2->GetXaxis()->SetTitleOffset(1.3);
h2->GetYaxis()->SetTitleOffset(1.3);
h2->SetMarkerStyle(23); h2->SetMarkerSize(2); h2->SetMarkerColor(4);
h3->SetMarkerStyle(33); h3->SetMarkerSize(2); h3->SetMarkerColor(2);
h4->SetMarkerStyle(29); h4->SetMarkerSize(2); h4->SetMarkerColor(1);
//h2->GetYaxis()->SetRange(0,10000);
h2->Draw();
h1->Draw("same");
h3->Draw("same");
h4->Draw("same");

h2->SetLineColor(1);
std::cout<<"SM: "<<h1->Integral()<<std::endl;
std::cout<<"aQGC_SM: "<<h2->Integral()<<std::endl;
std::cout<<"aQGC_Rewt: "<<h3->Integral()<<std::endl;
std::cout<<"aQGC_Rew_DS: "<<h4->Integral()<<std::endl;
auto legend = new TLegend(0.7,0.8,0.9,0.9);
legend->AddEntry(h1,"SM","lp");
legend->AddEntry(h2,"aQGC_SM","lp");
legend->AddEntry(h3,"aQGC_Rewt","lp");
legend->AddEntry(h4,"aQGC_Rewt_DS","lp");
legend->Draw();
//c1->SaveAs("aQGC.png");
//c1->SaveAs("SM.png");
c1->SaveAs("SM_aQGC_Com.png");
}
