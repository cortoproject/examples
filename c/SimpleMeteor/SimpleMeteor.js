if (Meteor.isClient) {
  remote = DDP.connect("127.0.0.1:8000");
  Temperature = new Meteor.Collection("Temperature", remote);
  remote.subscribe("Temperature", {value: true});

  Template.body.helpers({
    temperature: function () {
      return Temperature.find();
    }
  });
}

if (Meteor.isServer) {
  Meteor.startup(function () {
    // code to run on server at startup
  });
}
