/// <reference types="cypress" />

describe("Login", () => {
  beforeEach(() => {
    cy.visit("/");
  });

  it("Should have s address on account panel", () => {
    cy.get('[id="connectButton"]').click();
    cy.get('[id="mnemonicInput"]').type("s");
    cy.get('[id="mnemonicConnectButton"] > button').click();
    cy.get('[id="userInfoButton"]').click();
    cy.get('[id="addressWrapper"] > a > span').should(
      "contain",
      "band1jrhuqrymzt4mnvgw8cvy3s9zhx3jj0dq30qpte"
    );
  });
});

describe("Send", () => {
  it("Status should be Success", () => {
    cy.get('[id="getFreeButton"] > button').click();
    cy.get('[id="sendToken"] > button').wait(500).contains("Send").click();
    cy.get('[id="recipientAddressInput"]')
      .wait(5000)
      .type("band1jrhuqrymzt4mnvgw8cvy3s9zhx3jj0dq30qpte")
      .get('[id="sendAmountInput"]')
      .type("2");
    cy.get('[id="nextButton"]').contains("Next").click();
    cy.get('[id="broadcastButton"]').wait(1000).click();
    cy.get('[id="successMsgContainer"] > span').should(
      "contain",
      "Broadcast Transaction Success"
    );
    cy.get('[id="closeModal"]').click();
  });
});

describe("Delegation", () => {
  it("Should able to delegate with Carol", () => {
    cy.get('[id="nav-/validators"]').click();
    cy.get(
      '[id="nav-/validator/bandvaloper1j9vk75jjty02elhwqqjehaspfslaem8pr20qst#reports"]'
    )
      .wait(500)
      .click();
    cy.get('[id="validatorDelegationinfoDlegate"] button:nth-of-type(1)')
      .wait(1000)
      .click();
    cy.get('[id="nextButton"]').wait(1000).should("be.disabled");
    cy.get('[id="delegateAmountInput').type("10");
    cy.get('[id="memoInput"]').type("cypress");
    cy.get('[id="nextButton"]').click().wait(1000);
    cy.get('[id="broadcastButton"]').click().wait(1000);
    cy.get('[id="successMsgContainer"] > span').should(
      "contain",
      "Broadcast Transaction Success"
    );
    cy.get('[id="closeModal"]').click();
  });

  it("Should able to undelegate with Carol", () => {
    cy.get('[id="validatorDelegationinfoDlegate"] button:nth-of-type(2)')
      .wait(1000)
      .click();
    cy.get('[id="undelegateAmountInput').type("10");
    cy.get('[id="memoInput"]').type("cypress");
    cy.get('[id="nextButton"]').click().wait(1000);
    cy.get('[id="broadcastButton"]').click().wait(1000);
    cy.get('[id="successMsgContainer"] > span').should(
      "contain",
      "Broadcast Transaction Success"
    );
    cy.get('[id="closeModal"]').click();
  });
});
