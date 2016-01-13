if (Meteor.isClient) {
  remote = DDP.connect("127.0.0.1:8000");
  Stats = new Meteor.Collection("Stats", remote);
  Clients = new Meteor.Collection("ddp/__sessions", remote);
  remote.subscribe("Stats", {value: true});
  remote.subscribe("ddp/__sessions");

  var prevIdle = 0;
  var prevSys = 0;
  var prevUser = 0;

  Template.body.helpers({
    clients: function() {
      return Clients.find().count();
    },
    cpu: function () {
      var mon = Stats.findOne({_id: "mon"});
      var idle = mon.value.cpu.idle;
      var user = mon.value.cpu.user;
      var sys = mon.value.cpu.sys;
      var result = ((user - prevUser) + (sys - prevSys)) / (idle - prevIdle);
      prevIdle = idle;
      prevSys = sys;
      prevUser = user;
      return Math.round(result * 1000) / 10;
    },
    mem: function () {
      var mon = Stats.findOne({_id: "mon"});
      var used = mon.value.memory.actual_used;
      var total = mon.value.memory.total;
      var result = used / total;
      return Math.round(result * 1000) / 10;
    }
  });
  Template.cpus.helpers({
    cpu_info: function() {
      return Stats.findOne({_id: "mon"}).value.cpu_info;
    }
  });
}

if (Meteor.isServer) {
  Meteor.startup(function () {
    // code to run on server at startup
  });
}
